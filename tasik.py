import copy
import argparse
import time
from datetime import datetime
import collections

import cv2 as cv
import numpy as np
import tensorflow as tf # Assuming TFLite models need TensorFlow for loading


# --- Replicated Classes from your provided structure ---

# Replicating CvFpsCalc from utils.py
class CvFpsCalc:
    def __init__(self, buffer_len=10):
        self._start_tick = 0
        self._freq = 1000.0 / cv.getTickFrequency()
        self._difftimes = collections.deque(maxlen=buffer_len)

    def get(self):
        current_tick = cv.getTickCount()
        self._difftimes.append((current_tick - self._start_tick) * self._freq)
        self._start_tick = current_tick

        return 1000.0 / (sum(self._difftimes) / len(self._difftimes))

# Replicating FaceMesh from face_mesh/face_mesh.py
class FaceMesh:
    def __init__(
        self,
        max_num_faces=1,
        min_detection_confidence=0.7,
        min_tracking_confidence=0.7,
        # PATH TO YOUR FACEMESH MODEL FILE
        model_path='face_mesh_model.tflite' # <--- UPDATE THIS PATH IF NEEDED
    ):
        self.interpreter = tf.lite.Interpreter(model_path=model_path)
        self.interpreter.allocate_tensors()

        self.input_details = self.interpreter.get_input_details()
        self.output_details = self.interpreter.get_output_details()

        self.max_num_faces = max_num_faces
        self.min_detection_confidence = min_detection_confidence
        self.min_tracking_confidence = min_tracking_confidence

        # MediaPipe Face Mesh default constants (if not using MP library directly)
        # These are approximations. For official MP behavior, use the mediapipe package.
        # This part assumes a specific output structure from the TFLite model.
        # If your TFLite model is directly from MediaPipe, it might have more outputs.
        # This example focuses on bounding box and 468 landmarks.
        # The indices for eye bounding boxes within the 468 landmarks
        # These are simplified for the `calc_around_eye_bbox` method
        self.LEFT_EYE_LANDMARKS_FOR_BBOX = [33, 133, 160, 158, 144, 153] # Some points around left eye
        self.RIGHT_EYE_LANDMARKS_FOR_BBOX = [263, 362, 387, 385, 380, 373] # Some points around right eye

    def __call__(self, image):
        image_height, image_width = image.shape[0], image.shape[1]
        input_details_tensor_index = self.input_details[0]['index']
        input_shape = self.input_details[0]['shape']

        # Preprocess image for the model
        input_image = cv.resize(
            cv.cvtColor(image, cv.COLOR_BGR2RGB),
            (input_shape[1], input_shape[2])
        )
        input_image = np.expand_dims(input_image, axis=0)
        input_image = input_image.astype(np.float32) / 255.0 # Normalize to [0, 1]

        self.interpreter.set_tensor(input_details_tensor_index, input_image)
        self.interpreter.invoke()

        # Assuming output details:
        # output_details[0]: detection (e.g., bounding box and score)
        # output_details[1]: raw_landmarks (e.g., 468 3D facial landmarks)
        # This structure can vary depending on the exact TFLite model.
        # You may need to inspect your specific model's output details.
        # For simplicity, assuming a single output for landmarks.
        landmarks = self.interpreter.get_tensor(self.output_details[0]['index'])

        # Process landmarks (convert to original image coordinates)
        # This is a very simplified processing. A real MediaPipe FaceMesh model
        # often outputs multiple detections and scores, which would need filtering.
        # For a single face, we'll assume the first output is relevant.
        if landmarks.shape[1] > 0: # Check if any landmarks detected
            face_landmarks_list = []
            # Assuming landmarks is [1, 468, 3] for (x,y,z) coordinates
            # Convert normalized landmarks to pixel coordinates and create a mock object
            class MockLandmark:
                def __init__(self, x, y, z=0.0):
                    self.x = x
                    self.y = y
                    self.z = z

            landmarks_scaled = landmarks[0] # Take the first face's landmarks
            mock_face_landmarks = type('obj', (object,), {
                'landmark': [MockLandmark(lm[0], lm[1], lm[2]) for lm in landmarks_scaled]
            })()
            face_landmarks_list.append(mock_face_landmarks)
            return face_landmarks_list
        return []

    def calc_around_eye_bbox(self, face_landmarks):
        # Calculate bounding box around eyes based on MediaPipe landmarks
        # This function returns (x1, y1, x2, y2) for cropping
        all_landmarks = face_landmarks.landmark

        # Left Eye BBox
        left_eye_points = np.array([[all_landmarks[idx].x, all_landmarks[idx].y] for idx in self.LEFT_EYE_LANDMARKS_FOR_BBOX])
        min_x_l, min_y_l = np.min(left_eye_points, axis=0)
        max_x_l, max_y_l = np.max(left_eye_points, axis=0)
        left_eye_bbox = [min_x_l, min_y_l, max_x_l, max_y_l]

        # Right Eye BBox
        right_eye_points = np.array([[all_landmarks[idx].x, all_landmarks[idx].y] for idx in self.RIGHT_EYE_LANDMARKS_FOR_BBOX])
        min_x_r, min_y_r = np.min(right_eye_points, axis=0)
        max_x_r, max_y_r = np.max(right_eye_points, axis=0)
        right_eye_bbox = [min_x_r, min_y_r, max_x_r, max_y_r]

        # Scale to pixel coordinates (assuming input landmarks are normalized [0,1])
        # This will be done in the main loop for the image, but here we just pass normalized.
        # The main loop will scale them when applying to image crops.
        return left_eye_bbox, right_eye_bbox

# Replicating IrisLandmark from iris_landmark/iris_landmark.py
class IrisLandmark:
    def __init__(
        self,
        # PATH TO YOUR IRIS LANDMARK MODEL FILE
        model_path='iris_landmark_model.tflite' # <--- UPDATE THIS PATH IF NEEDED
    ):
        self.interpreter = tf.lite.Interpreter(model_path=model_path)
        self.interpreter.allocate_tensors()

        self.input_details = self.interpreter.get_input_details()
        self.output_details = self.interpreter.get_output_details()

    def __call__(self, eye_image):
        input_shape = self.input_details[0]['shape']
        input_details_tensor_index = self.input_details[0]['index']

        # Preprocess eye image for the model
        input_eye_image = cv.resize(
            cv.cvtColor(eye_image, cv.COLOR_BGR2RGB),
            (input_shape[1], input_shape[2])
        )
        input_eye_image = np.expand_dims(input_eye_image, axis=0)
        input_eye_image = input_eye_image.astype(np.float32) / 255.0 # Normalize to [0, 1]

        self.interpreter.set_tensor(input_details_tensor_index, input_eye_image)
        self.interpreter.invoke()

        # Assuming output details:
        # output_details[0]: eye_contour_landmarks (16 points, 3D)
        # output_details[1]: iris_landmarks (5 points, 3D)
        # This structure can vary. Check your specific model.
        eye_contour_landmarks = self.interpreter.get_tensor(self.output_details[0]['index'])[0] # Take first (and only) result
        iris_landmarks = self.interpreter.get_tensor(self.output_details[1]['index'])[0] # Take first (and only) result

        return eye_contour_landmarks, iris_landmarks

    def get_input_shape(self):
        return self.input_details[0]['shape'][1], self.input_details[0]['shape'][2]

# --- Constants and Model Points (from previous combined code) ---
LEFT_EYE_MP_IDX = [33, 160, 158, 133, 153, 144]
RIGHT_EYE_MP_IDX = [362, 385, 387, 263, 373, 380]

EAR_THRESHOLD = 0.21
ARROW_SCALE = 5.0

MODEL_POINTS_HEAD = np.array([
    (0.0, 0.0, 0.0),        # Nose tip (landmark 1)
    (0.0, -330.0, -65.0),   # Chin (landmark 152)
    (-225.0, 170.0, -135.0), # Left eye outer (landmark 33)
    (225.0, 170.0, -135.0),  # Right eye outer (landmark 263)
    (-150.0, -150.0, -125.0),# Left mouth corner (landmark 61)
    (150.0, -150.0, -125.0)  # Right mouth corner (landmark 291)
], dtype=np.float64)

# Generic Eye/Iris Model Points for the IrisLandmark output (5 iris points)
MODEL_POINTS_IRIS = np.array([
    (0.0, 0.0, 0.0),      # Center (conceptual)
    (-0.5, 0.0, 0.0),     # Leftmost iris point
    (0.5, 0.0, 0.0),      # Rightmost iris point
    (0.0, 0.5, 0.0),      # Topmost iris point
    (0.0, -0.5, 0.0),     # Bottommost iris point
], dtype=np.float64)


# --- Utility Functions (retained and modified) ---
def calculate_ear(eye_landmarks):
    """Calculates the Eye Aspect Ratio (EAR) for a given eye using MediaPipe indices."""
    A = np.linalg.norm(eye_landmarks[1] - eye_landmarks[5])
    B = np.linalg.norm(eye_landmarks[2] - eye_landmarks[4])
    C = np.linalg.norm(eye_landmarks[0] - eye_landmarks[3])
    ear = (A + B) / (2.0 * C)
    return ear

def get_gaze_vector(iris_center, eye_points_outer_corners):
    """Estimates a 2D gaze vector from iris center and eye horizontal extremities."""
    eye_center = (eye_points_outer_corners[0] + eye_points_outer_corners[1]) / 2.0
    gaze_vector = np.array(iris_center) - eye_center
    return gaze_vector

def rotation_vector_to_euler_angles(rvec):
    """Converts a Rodrigues rotation vector to Euler angles (roll, pitch, yaw)."""
    R, _ = cv.Rodrigues(rvec)
    sy = np.sqrt(R[0,0] * R[0,0] + R[1,0] * R[1,0])
    singular = sy < 1e-6
    if not singular:
        x = np.arctan2(R[2,1], R[2,2]) # Pitch
        y = np.arctan2(-R[2,0], sy)    # Yaw
        z = np.arctan2(R[1,0], R[0,0]) # Roll
    else:
        x = np.arctan2(-R[1,2], R[1,1])
        y = np.arctan2(-R[2,0], sy)
        z = 0
    pitch = np.degrees(x)
    yaw = np.degrees(y)
    roll = np.degrees(z)
    return roll, pitch, yaw

def detect_iris(image, iris_detector, left_eye_bbox, right_eye_bbox):
    """Detects iris landmarks within cropped eye bounding boxes."""
    image_width, image_height = image.shape[1], image.shape[0]
    input_shape = iris_detector.get_input_shape()

    left_iris_points = []
    right_iris_points = []
    
    # Left eye
    left_eye_x1 = max(int(left_eye_bbox[0] * image_width), 0)
    left_eye_y1 = max(int(left_eye_bbox[1] * image_height), 0)
    left_eye_x2 = min(int(left_eye_bbox[2] * image_width), image_width)
    left_eye_y2 = min(int(left_eye_bbox[3] * image_height), image_height)
    
    if left_eye_x2 > left_eye_x1 and left_eye_y2 > left_eye_y1:
        left_eye_image = image[left_eye_y1:left_eye_y2, left_eye_x1:left_eye_x2]
        if left_eye_image.size > 0:
            eye_contour_l, iris_l = iris_detector(left_eye_image)
            left_iris_points = calc_iris_point(
                [left_eye_x1, left_eye_y1, left_eye_x2, left_eye_y2], # Pass absolute bbox
                eye_contour_l, iris_l, input_shape
            )

    # Right eye
    right_eye_x1 = max(int(right_eye_bbox[0] * image_width), 0)
    right_eye_y1 = max(int(right_eye_bbox[1] * image_height), 0)
    right_eye_x2 = min(int(right_eye_bbox[2] * image_width), image_width)
    right_eye_y2 = min(int(right_eye_bbox[3] * image_height), image_height)

    if right_eye_x2 > right_eye_x1 and right_eye_y2 > right_eye_y1:
        right_eye_image = image[right_eye_y1:right_eye_y2, right_eye_x1:right_eye_x2]
        if right_eye_image.size > 0:
            eye_contour_r, iris_r = iris_detector(right_eye_image)
            right_iris_points = calc_iris_point(
                [right_eye_x1, right_eye_y1, right_eye_x2, right_eye_y2], # Pass absolute bbox
                eye_contour_r, iris_r, input_shape
            )

    return left_iris_points, right_iris_points


def calc_iris_point(eye_bbox_abs, eye_contour_raw, iris_raw_points, input_shape):
    """
    Converts iris and eye contour coordinates from relative (model output)
    to absolute pixel coordinates based on the original image crop.
    Returns a list of (x,y) tuples for the 5 iris points.
    """
    iris_list = []
    bbox_width = eye_bbox_abs[2] - eye_bbox_abs[0]
    bbox_height = eye_bbox_abs[3] - eye_bbox_abs[1]
    input_width, input_height = input_shape[0], input_shape[1] # Model's input width/height

    for i in range(5):
        # Scale the normalized point from model's input size to bbox size
        point_x_bbox = iris_raw_points[i * 3] * (bbox_width / input_width)
        point_y_bbox = iris_raw_points[i * 3 + 1] * (bbox_height / input_height)

        # Add the offset of the bbox's top-left corner
        point_x = int(point_x_bbox + eye_bbox_abs[0])
        point_y = int(point_y_bbox + eye_bbox_abs[1])

        iris_list.append((point_x, point_y))
    return iris_list


def calc_min_enc_losingCircle(landmark_list):
    """Calculates the minimum enclosing circle for a list of points."""
    if not landmark_list or len(landmark_list) < 2: # Need at least 2 points for a circle
        return (0,0), 0
    center, radius = cv.minEnclosingCircle(np.array(landmark_list).astype(np.float32))
    center = (int(center[0]), int(center[1]))
    radius = int(radius)
    return center, radius

def draw_debug_image(
    debug_image,
    mp_mesh_points, # MediaPipe face landmarks for drawing head pose axis
    left_iris_points,
    right_iris_points,
    left_center,
    left_radius,
    right_center,
    right_radius,
    log_data,
    display_fps,
    camera_matrix,
    dist_coeffs,
    rvec_head,
    tvec_head
):
    h, w = debug_image.shape[:2]

    # Draw head pose axis
    if rvec_head is not None and tvec_head is not None:
        cv.drawFrameAxes(debug_image, camera_matrix, dist_coeffs, rvec_head, tvec_head, 50)

    # Draw iris: circumscribed circle
    cv.circle(debug_image, left_center, left_radius, (0, 255, 0), 2)
    cv.circle(debug_image, right_center, right_radius, (0, 255, 0), 2)

    # Draw iris: landmark points
    for point in left_iris_points:
        cv.circle(debug_image, (point[0], point[1]), 1, (0, 0, 255), 2)
    for point in right_iris_points:
        cv.circle(debug_image, (point[0], point[1]), 1, (0, 0, 255), 2)

    # Gaze Arrows (using iris center and gaze vector from log_data)
    # Reconstruct gaze vector from logged data for drawing
    left_gaze = np.array([log_data["gaze_direction_left_x"], log_data["gaze_direction_left_y"]])
    right_gaze = np.array([log_data["gaze_direction_right_x"], log_data["gaze_direction_right_y"]])

    if left_center != (0,0) and np.linalg.norm(left_gaze) > 0.1: # Draw only if valid gaze
        left_arrow_end = (int(left_center[0] + ARROW_SCALE * left_gaze[0]),
                          int(left_center[1] + ARROW_SCALE * left_gaze[1]))
        cv.arrowedLine(debug_image, left_center, left_arrow_end, (0, 255, 0), 2, tipLength=0.3)

    if right_center != (0,0) and np.linalg.norm(right_gaze) > 0.1:
        right_arrow_end = (int(right_center[0] + ARROW_SCALE * right_gaze[0]),
                           int(right_center[1] + ARROW_SCALE * right_gaze[1]))
        cv.arrowedLine(debug_image, right_center, right_arrow_end, (0, 255, 0), 2, tipLength=0.3)


    # Display iris radius
    cv.putText(debug_image, 'r:' + str(left_radius) + 'px',
               (left_center[0] + int(left_radius * 1.5), left_center[1] + int(left_radius * 0.5)),
               cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 1)
    cv.putText(debug_image, 'r:' + str(right_radius) + 'px',
               (right_center[0] + int(right_radius * 1.5), right_center[1] + int(right_radius * 0.5)),
               cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 1)

    # --- Display Information ---
    cv.putText(debug_image, f"FPS: {display_fps:.2f}", (10, 30),
                   cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2, cv.LINE_AA)
    cv.putText(debug_image, f"Blink: {log_data['blink_status']} ({log_data['last_blink_duration_sec']:.2f}s)",
                (10, 60), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 255), 2)

    cv.putText(debug_image, f"Head Roll: {log_data['head_roll']:.2f} deg",
                (10, 90), cv.FONT_HERSHEY_SIMPLEX, 0.7, (255, 0, 0), 2)
    cv.putText(debug_image, f"Head Pitch: {log_data['head_pitch']:.2f} deg",
                (10, 120), cv.FONT_HERSHEY_SIMPLEX, 0.7, (255, 0, 0), 2)
    cv.putText(debug_image, f"Head Yaw: {log_data['head_yaw']:.2f} deg",
                (10, 150), cv.FONT_HERSHEY_SIMPLEX, 0.7, (255, 0, 0), 2)

    cv.putText(debug_image, f"L Eye Roll: {log_data['left_eye_roll']:.2f} deg",
                (w - 250, 30), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    cv.putText(debug_image, f"L Eye Pitch: {log_data['left_eye_pitch']:.2f} deg",
                (w - 250, 60), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    cv.putText(debug_image, f"L Eye Yaw: {log_data['left_eye_yaw']:.2f} deg",
                (w - 250, 90), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    cv.putText(debug_image, f"R Eye Roll: {log_data['right_eye_roll']:.2f} deg",
                (w - 250, 120), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    cv.putText(debug_image, f"R Eye Pitch: {log_data['right_eye_pitch']:.2f} deg",
                (w - 250, 150), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    cv.putText(debug_image, f"R Eye Yaw: {log_data['right_eye_yaw']:.2f} deg",
                (w - 250, 180), cv.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)


    return debug_image


def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--device", type=int, default=0)
    parser.add_argument("--width", help='cap width', type=int, default=960)
    parser.add_argument("--height", help='cap height', type=int, default=540)
    parser.add_argument("--max_num_faces", type=int, default=1)
    parser.add_argument("--min_detection_confidence", type=float, default=0.7)
    parser.add_argument("--min_tracking_confidence", type=float, default=0.7) # Changed to float for consistency
    args = parser.parse_args()
    return args

def main():
    args = get_args()

    cap_device = args.device
    cap_width = args.width
    cap_height = args.height

    max_num_faces = args.max_num_faces
    min_detection_confidence = args.min_detection_confidence
    min_tracking_confidence = args.min_tracking_confidence

    cap = cv.VideoCapture(cap_device)
    cap.set(cv.CAP_PROP_FRAME_WIDTH, cap_width)
    cap.set(cv.CAP_PROP_FRAME_HEIGHT, cap_height)

    # Initialize FaceMesh and IrisLandmark models
    # MAKE SURE YOUR .TFLITE MODELS ARE IN THE SAME DIRECTORY OR UPDATE PATHS HERE
    try:
        face_mesh_model_path = 'face_mesh_model.tflite'
        iris_landmark_model_path = 'iris_landmark_model.tflite'
        face_mesh = FaceMesh(
            max_num_faces,
            min_detection_confidence,
            min_tracking_confidence,
            model_path=face_mesh_model_path
        )
        iris_detector = IrisLandmark(model_path=iris_landmark_model_path)
    except Exception as e:
        print(f"Error loading TFLite models: {e}")
        print("Please ensure 'face_mesh_model.tflite' and 'iris_landmark_model.tflite' are in the same directory.")
        print("Or update the 'model_path' in FaceMesh and IrisLandmark class constructors.")
        return # Exit if models can't be loaded

    cvFpsCalc = CvFpsCalc(buffer_len=10)

    # --- Blink Tracking Variables ---
    blink_start_time = None
    last_blink_duration = 0.0
    is_blinking = False

    # --- CSV Logging Setup ---
    csv_file = open("gaze_and_pose_tracking_combined.csv", mode='w', newline='')
    csv_writer = csv.writer(csv_file)
    csv_writer.writerow([
        "timestamp",
        "blink_status", "last_blink_duration_sec",
        "left_pupil_x", "left_pupil_y",
        "right_pupil_x", "right_pupil_y",
        "gaze_direction_left_x", "gaze_direction_left_y",
        "gaze_direction_right_x", "gaze_direction_right_y",
        "head_roll", "head_pitch", "head_yaw",
        "head_tx", "head_ty", "head_tz",
        "left_eye_roll", "left_eye_pitch", "left_eye_yaw",
        "right_eye_roll", "right_eye_pitch", "right_eye_yaw"
    ])

    # Camera parameters (updated dynamically if resolution changes)
    focal_length = cap_width
    center = (cap_width / 2, cap_height / 2)
    camera_matrix = np.array([
        [focal_length, 0, center[0]],
        [0, focal_length, center[1]],
        [0, 0, 1]
    ], dtype="double")
    dist_coeffs = np.zeros((4, 1))

    while True:
        display_fps = cvFpsCalc.get()

        ret, image = cap.read()
        if not ret:
            break
        image = cv.flip(image, 1)
        debug_image = copy.deepcopy(image)
        h, w = image.shape[:2]

        # Update camera matrix based on current frame dimensions
        if w != camera_matrix[0, 0] or h != camera_matrix[1, 1]:
            focal_length = w # Simple assumption: focal length scales with width
            center = (w / 2, h / 2)
            camera_matrix = np.array([
                [focal_length, 0, center[0]],
                [0, focal_length, center[1]],
                [0, 0, 1]
            ], dtype="double")

        # Initialize log data for the current frame
        log_data = {
            "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f"),
            "blink_status": "Open", "last_blink_duration_sec": 0.0,
            "left_pupil_x": 0, "left_pupil_y": 0,
            "right_pupil_x": 0, "right_pupil_y": 0,
            "gaze_direction_left_x": 0.0, "gaze_direction_left_y": 0.0,
            "gaze_direction_right_x": 0.0, "gaze_direction_right_y": 0.0,
            "head_roll": 0.0, "head_pitch": 0.0, "head_yaw": 0.0,
            "head_tx": 0.0, "head_ty": 0.0, "head_tz": 0.0,
            "left_eye_roll": 0.0, "left_eye_pitch": 0.0, "left_eye_yaw": 0.0,
            "right_eye_roll": 0.0, "right_eye_pitch": 0.0, "right_eye_yaw": 0.0
        }
        
        # Initialize rvec_head and tvec_head for drawing in case solvePnP fails
        rvec_head_for_draw, tvec_head_for_draw = None, None

        # Face Mesh detection (for head pose and general eye landmarks for EAR)
        face_results = face_mesh(image)

        if face_results: # Process only if a face is detected
            for face_result in face_results:
                # Convert normalized MediaPipe landmarks to pixel coordinates
                # Assuming landmarks from FaceMesh.__call__ are normalized [0,1]
                mp_mesh_points = np.array([(lm.x * w, lm.y * h) for lm in face_result.landmark])

                # --- Head Pose Estimation (using MediaPipe landmarks) ---
                image_points_head = np.array([
                    mp_mesh_points[1],     # Nose tip
                    mp_mesh_points[152],   # Chin
                    mp_mesh_points[33],    # Left eye outer corner
                    mp_mesh_points[263],   # Right eye outer corner
                    mp_mesh_points[61],    # Left mouth corner
                    mp_mesh_points[291],   # Right mouth corner
                ], dtype=np.float64)

                if image_points_head.shape[0] == MODEL_POINTS_HEAD.shape[0]: # Ensure point count matches
                    success_pnp_head, rvec_head, tvec_head = cv.solvePnP(
                        MODEL_POINTS_HEAD, image_points_head, camera_matrix, dist_coeffs, flags=cv.SOLVEPNP_ITERATIVE
                    )
                    rvec_head_for_draw, tvec_head_for_draw = rvec_head, tvec_head # Store for drawing later

                    if success_pnp_head:
                        head_roll, head_pitch, head_yaw = rotation_vector_to_euler_angles(rvec_head)
                        log_data["head_roll"] = head_roll
                        log_data["head_pitch"] = head_pitch
                        log_data["head_yaw"] = head_yaw
                        log_data["head_tx"] = tvec_head[0][0]
                        log_data["head_ty"] = tvec_head[1][0]
                        log_data["head_tz"] = tvec_head[2][0]
                
                # --- Blink Detection (using MediaPipe landmarks) ---
                left_eye_mp_points_ear = np.array([mp_mesh_points[idx] for idx in LEFT_EYE_MP_IDX])
                right_eye_mp_points_ear = np.array([mp_mesh_points[idx] for idx in RIGHT_EYE_MP_IDX])

                # Check if we have enough points for EAR calculation
                if len(left_eye_mp_points_ear) == 6 and len(right_eye_mp_points_ear) == 6:
                    left_ear = calculate_ear(left_eye_mp_points_ear)
                    right_ear = calculate_ear(right_eye_mp_points_ear)
                    ear_avg = (left_ear + right_ear) / 2.0

                    if ear_avg < EAR_THRESHOLD:
                        if not is_blinking:
                            blink_start_time = time.time()
                            is_blinking = True
                        log_data["blink_status"] = "Blink"
                    else:
                        if is_blinking:
                            last_blink_duration = time.time() - blink_start_time
                            log_data["last_blink_duration_sec"] = last_blink_duration
                            blink_start_time = None
                            is_blinking = False
                        else:
                            log_data["last_blink_duration_sec"] = last_blink_duration
                        log_data["blink_status"] = "Open"


                # --- Iris Detection (using IrisLandmark model) ---
                # calc_around_eye_bbox returns normalized bbox coords
                left_eye_bbox_norm, right_eye_bbox_norm = face_mesh.calc_around_eye_bbox(face_result)
                
                left_iris_points, right_iris_points = detect_iris(
                    image, iris_detector, left_eye_bbox_norm, right_eye_bbox_norm
                )

                left_iris_center, left_radius = calc_min_enc_losingCircle(left_iris_points)
                right_iris_center, right_radius = calc_min_enc_losingCircle(right_iris_points)

                log_data["left_pupil_x"] = left_iris_center[0]
                log_data["left_pupil_y"] = left_iris_center[1]
                log_data["right_pupil_x"] = right_iris_center[0]
                log_data["right_pupil_y"] = right_iris_center[1]

                # --- Gaze Position (using IrisLandmark iris center and MediaPipe eye corners) ---
                left_eye_horizontal_extremities = [mp_mesh_points[133], mp_mesh_points[33]] # Inner, Outer MP points
                right_eye_horizontal_extremities = [mp_mesh_points[263], mp_mesh_points[362]] # Inner, Outer MP points

                if left_iris_center != (0,0) and np.linalg.norm(np.array(left_eye_horizontal_extremities[0])-np.array(left_eye_horizontal_extremities[1])) > 0: # Ensure valid eye span
                    left_gaze = get_gaze_vector(np.array(left_iris_center), np.array(left_eye_horizontal_extremities))
                    log_data["gaze_direction_left_x"] = left_gaze[0]
                    log_data["gaze_direction_left_y"] = left_gaze[1]

                if right_iris_center != (0,0) and np.linalg.norm(np.array(right_eye_horizontal_extremities[0])-np.array(right_eye_horizontal_extremities[1])) > 0:
                    right_gaze = get_gaze_vector(np.array(right_iris_center), np.array(right_eye_horizontal_extremities))
                    log_data["gaze_direction_right_x"] = right_gaze[0]
                    log_data["gaze_direction_right_y"] = right_gaze[1]


                # --- Individual Eye Pose (Roll, Pitch, Yaw of Eye Movement) ---
                if len(left_iris_points) == 5:
                    image_points_l_iris = np.array(left_iris_points, dtype=np.float64)
                    success_pnp_l_eye, rvec_l_eye, tvec_l_eye = cv.solvePnP(
                        MODEL_POINTS_IRIS, image_points_l_iris, camera_matrix, dist_coeffs, flags=cv.SOLVEPNP_ITERATIVE
                    )
                    if success_pnp_l_eye:
                        l_eye_roll, l_eye_pitch, l_eye_yaw = rotation_vector_to_euler_angles(rvec_l_eye)
                        log_data["left_eye_roll"] = l_eye_roll
                        log_data["left_eye_pitch"] = l_eye_pitch
                        log_data["left_eye_yaw"] = l_eye_yaw

                if len(right_iris_points) == 5:
                    image_points_r_iris = np.array(right_iris_points, dtype=np.float64)
                    success_pnp_r_eye, rvec_r_eye, tvec_r_eye = cv.solvePnP(
                        MODEL_POINTS_IRIS, image_points_r_iris, camera_matrix, dist_coeffs, flags=cv.SOLVEPNP_ITERATIVE
                    )
                    if success_pnp_r_eye:
                        r_eye_roll, r_eye_pitch, r_eye_yaw = rotation_vector_to_euler_angles(rvec_r_eye)
                        log_data["right_eye_roll"] = r_eye_roll
                        log_data["right_eye_pitch"] = r_eye_pitch
                        log_data["right_eye_yaw"] = r_eye_yaw

                # Draw debug image elements
                debug_image = draw_debug_image(
                    debug_image,
                    mp_mesh_points, # Pass MediaPipe points for drawing if needed
                    left_iris_points,
                    right_iris_points,
                    left_iris_center,
                    left_radius,
                    right_iris_center,
                    right_radius,
                    log_data,
                    display_fps,
                    camera_matrix,
                    dist_coeffs,
                    rvec_head_for_draw, # Use the stored rvec,tvec for drawing
                    tvec_head_for_draw
                )

        # Write logged data to CSV
        csv_writer.writerow([
            log_data["timestamp"],
            log_data["blink_status"], log_data["last_blink_duration_sec"],
            log_data["left_pupil_x"], log_data["left_pupil_y"],
            log_data["right_pupil_x"], log_data["right_pupil_y"],
            log_data["gaze_direction_left_x"], log_data["gaze_direction_left_y"],
            log_data["gaze_direction_right_x"], log_data["gaze_direction_right_y"],
            log_data["head_roll"], log_data["head_pitch"], log_data["head_yaw"],
            log_data["head_tx"], log_data["head_ty"], log_data["head_tz"],
            log_data["left_eye_roll"], log_data["left_eye_pitch"], log_data["left_eye_yaw"],
            log_data["right_eye_roll"], log_data["right_eye_pitch"], log_data["right_eye_yaw"]
        ])

        cv.imshow('Integrated Eye & Head Tracking', debug_image)

        key = cv.waitKey(1)
        if key == 27: # ESC key to exit
            break

    cap.release()
    csv_file.close()
    cv.destroyAllWindows()


if __name__ == '__main__':
    main()
```
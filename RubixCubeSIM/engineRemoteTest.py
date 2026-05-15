import ctypes
import os

script_dir = os.path.dirname(os.path.abspath(__file__))
lib_path = os.path.join(script_dir, 'cube_engine.dll') 
cube_lib = ctypes.CDLL(lib_path)


CubeArrayType = (ctypes.c_int * 9) * 6

cube_lib.simulateCubeMove.argtypes =  [CubeArrayType, ctypes.c_int]
cube_lib.simulateCubeMove.restype = ctypes.c_int

def create_solved_cube():
   return CubeArrayType(
        (0, 0, 0, 0, 0, 0, 0 , 0, 0),  
        (1, 1, 1, 1, 1, 1, 1, 1, 1),
        (2, 2, 2, 2, 2, 2, 2 , 2, 2),  
        (4, 4, 4, 4, 4, 4, 4, 4, 4), 
        (5, 5, 5, 5, 5, 5, 5, 5, 5)  
    )

def print_cube_state(cube):
    print("\n--- Current Array State --- ")
    for face in range(6):
        row_vals = [cube[face][i] for i  in range(9)]
        print(f"Face {face}: {row_vals}")
    print("---------------------------\n")

if __name__ == "__main__":
    my_cube = create_solved_cube()
    print("Cube Initialized!")
    print_cube_state(my_cube)
    while True:
        try:
            move = int(input("Enter move (1-9 CW, 11-19 CCW, 0 to quit): "))
            if move == 0:
                break
            cube_lib.simulateCubeMove(my_cube, move)
            print_cube_state(my_cube)          
        except ValueError:
            print("Please enter a valid number.")
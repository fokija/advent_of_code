with open("input_1.txt", "r") as file:
    line_arr_str = []
    left_column_int = []
    right_column_int = []
    distance_arr_int = []
    total_distance = 0

    for line in file:
        line_arr_str.append(line)
    
    for line in line_arr_str:
        left_column_int.append(int(line[:5]))
        right_column_int.append(int(line[-6:]))

    left_column_int.sort()
    right_column_int.sort()

    idx = 0
    while idx < len(left_column_int):
        distance_arr_int.append(abs(right_column_int[idx] - left_column_int[idx]))
        idx += 1

    for idx in distance_arr_int:
        total_distance += idx
    
    print(total_distance)


    
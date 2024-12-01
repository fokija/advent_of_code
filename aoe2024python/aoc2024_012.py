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

    for left_idx in left_column_int:
        counter = 0
        for right_idx in right_column_int:
            if left_idx == right_idx:
                counter += 1
        distance_arr_int.append(left_idx * counter)
        counter = 0

    for idx in  distance_arr_int:
        total_distance += idx
    
    print(total_distance)

    
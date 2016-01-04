
def fifo(rand_ref_str, frame_number):
    frames = []
    page_fault_time = 0
    for i in range(0, len(rand_ref_str)):
        if rand_ref_str[i] not in frames:
            page_fault_time += 1
            frames.append(rand_ref_str[i])
            if len(frames) > frame_number:
                del frames[0]
            print(frames)
    print("page fault time: ", str(page_fault_time))


def lru(rand_ref_str, frame_number):
    frames = []
    page_fault_time = 0
    for i in range(0, len(rand_ref_str)):
        if rand_ref_str[i] not in frames:
            page_fault_time += 1
            frames.append(rand_ref_str[i])
            if len(frames) > frame_number:
                del frames[0]
            print(frames)
        else:
            frames.remove(rand_ref_str[i])
            frames.append(rand_ref_str[i])
    print("page fault time: " + str(page_fault_time))


def opt(rand_ref_str, frame_number):
    frames = []
    page_fault_time = 0
    for i in range(0, len(rand_ref_str)):
        if rand_ref_str[i] not in frames:
            page_fault_time += 1
            if len(frames) == frame_number:
                stack = []
                for j in range(i+1, len(rand_ref_str)):
                    if rand_ref_str[j] in frames and rand_ref_str[j] not in stack:
                        stack.append(rand_ref_str[j])
                replace_val = -1
                if len(stack) > 0:
                    replace_val = stack[-1]
                for j in range(0, len(frames)):
                    if frames[j] not in stack:
                        replace_val = frames[j]
                        break
                frames.remove(replace_val)
            frames.append(rand_ref_str[i])
            print(frames)
    print("page fault time: ", str(page_fault_time))

if __name__ == '__main__':
    rand_str = [int(i) for i in list(input())]
    print(rand_str)
    frame_num = 3

    fifo(rand_str, frame_num)
    lru(rand_str, frame_num)
    opt(rand_str, frame_num)

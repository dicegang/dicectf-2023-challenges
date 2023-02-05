import copy

processed = "m_ERpmfrNkekU4_4asI_Tra1e_4l_c4_GCDlryidS3{Ptsu9i}13Es4V73M4_ans"

size = 8

thread_buffers = []
for i in range(8):
    thread_buffers.append(list(processed[i * 8:(i + 1) * 8]))
for iteration in range(10000 - 1, -1, -1):
    new_thread_buffers = copy.deepcopy(thread_buffers)

    slot = iteration % 8

    for rank, buffer in enumerate(thread_buffers):
        destination = ((rank - iteration) % size + size) % size
        source = ((rank + iteration) % size + size) % size

        new_thread_buffers[source][slot] = thread_buffers[rank][slot]
        new_thread_buffers[rank][slot] = thread_buffers[destination][slot]

    thread_buffers = new_thread_buffers

swaps = [26, 32, 14, 11, 3, 1, 32, 24, 13, 17, 3, 17, 2, 13, 19, 6, 12, 22, 3, 30, 10, 6, 8, 26, 6, 22,
         13, 1, 19, 1, 1, 29]

permuted = []
for x in thread_buffers:
    permuted += x

for i in range(32 - 1, -1, -1):
    permuted[i], permuted[swaps[i] + 31] = permuted[swaps[i] + 31], permuted[i]

print(''.join(permuted))

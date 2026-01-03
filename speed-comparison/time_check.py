

import time

start = time.time()

output = ""

for i in  range(100000) : output += str(i) + "\n"

print(output, "Time Taken by Python :",
	(time.time()-start)*1000, "ms")
N = int(input("N = "))

switches = [False] * N

def print_switches(arr:list) :
    return "".join(
        "1" if on else "0" for on in arr
    )

print(f"Kondisi awal saklar: {print_switches(switches)}")

for robohand in range(1, N+1) :
    print(f"Gerakan Tangan Robot {robohand}")
    print("---------------------------------")
    pressed = 0
    for switch in range(robohand-1, N, robohand) : 
        switches[switch] = not switches[switch]
        pressed += 1
        print(f"Tekan tombol ke {pressed} {print_switches(switches)}")
    print()

print(f"Banyak saklar yang masih menyala: {sum([1 for i in switches if i])}")
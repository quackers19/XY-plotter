import serial
import time


def gcode():
    arduino = serial.Serial(port='COM5', baudrate=9600, timeout=.2)
    # 🔽EDIT THIS LINE TO CHANGE GCODE FILE🔽
    code = open(r"C:\\Users\\Liam Tighe\\OneDrive - St Peters Lutheran College\\Documents\\XY plotter\\juicy-gcode-0.2.0.1\\test.gcode", 'r')
    raw = []
    cmdlist = []

    def write(x):
        arduino.write(bytes(x, 'utf-8'))

    def read():
        return arduino.readline().decode('utf-8')

    for line in code:
        raw.append(line)
    for cmd in raw:
        try:
            cmdlist.append(cmd.rstrip("\n"))
        except:
            cmdlist.append(cmd)
    code.close()

    while read() != "ready":
        time.sleep(.5)
    print("ready")

    for cmd in cmdlist:
        write(cmd)
        status = read()
        while status != "next":
            time.sleep(.25)
            status = read()
        print('next')  
    

    
    print('finished')

if __name__ == "__main__":
    gcode()
# recognize speech from microphone

import speech_recognition as sr
import serial

ser = serial.Serial('/dev/tty.usbserial-1410', 9600)
r = sr.Recognizer()
with sr.Microphone() as source:
    print("Calibrating ambient noise")
    r.adjust_for_ambient_noise(source)
status = True
startup = False

# startup configuration-----------------------------
while startup == False:
    r = sr.Recognizer()
    with sr.Microphone() as source:    
        print("Awaiting startup")
        audio = r.listen(source)
    try:
        print("Command is: " + r.recognize_google(audio))
        command = r.recognize_google(audio)
        if "start" or "auto" or "roll" in command:
            startup = True
            print("starting")
            ser.write(b'0')
    except sr.UnknownValueError:
        print("could not hear message")
        startup = False
    except sr.RequestError as e:
        print("request error")
        startup = False

# movement controls--------------------------------
while status == True:
    r = sr.Recognizer()
    with sr.Microphone() as source:    
        print("Say something!")
        audio = r.listen(source)
    try:
        command = r.recognize_google(audio)
        print("Command is: " + command)
        if "stop" in command:
            st = "S"
            print(st)
            ser.write(b'6')
        elif "forward" in command:
            st = "F"
            print(st)
            ser.write(b'1')
        elif "backward" in command or "back" in command:
            st = "B"
            print(st)
            ser.write(b'2')
        elif "right" in command:
            st = "R"
            print(st)
            ser.write(b'3')
        elif "left" in command:
            st = "L"
            print(st)
            ser.write(b'4')
        elif "dance" in command:
            st = "D"
            print(st)
            ser.write(b'5')
        elif "reverse" in command:
            if st == "F":
                st = "B"
                print(st)
                ser.write(b'2')
            elif st == "B":
                st = "F"
                print(st)
                ser.write(b'1')
            elif st == "L":
                st = "R"
                print(st)
                ser.write(b'3')
            elif st == "R":
                st = "L"
                print(st)
                ser.write(b'4')
            else:
                st = "S"
                print(st)
                ser.write(b'6')
        else:
            pass
    except sr.UnknownValueError:
        print("could not hear message")
        ser.write(b'7')
    except sr.RequestError as e:
        print("request error")
        ser.write(b'7')


#!/usr/bin/python 

file = open('ports.conf');

print(file.read());

file.seek(0, 0);
line = file.readline();
while line != "":
    print("Line :: " + line.strip());
    line = file.readline();

file.seek(0, 0);
for line in file.readlines():
    print("Line :: " + line.strip());

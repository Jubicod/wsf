import sys
import subprocess


def parsehex(s):
    o = ''
    if len(s) == 0:
        return o
    if s[0] == 'w':
        n = 4
    if s[0] == 'h':
        n = 2
    if s[0] == 'b':
        n = 1
    for i in range(0,n*2,2)[::-1]:
        o += bytearray(chr(int(s[i+1:i+3],16)))
    return o + parseascii(s[1+n*2:])

def parseascii(s):
    o = ''
    t = s.split('\\',1)
    o += bytearray(t[0])
    if len(t) == 2:
        return o + parsehex(t[1])
    else: 
        return o

    
    
if len(sys.argv) > 1:  
    out = ''    
    for a in sys.argv[1:]:
        out += parseascii(a) + bytearray('\x0a')
    print(out)
else:
    print('tobin.py string1 string2 ...')
    print('convert and concatenate ascii strings to one single binary string')
    print('special characters:')
    print('  \\b : following two characters are converted into a byte')
    print('  \\h : following four characters are converted into a little endian 16 bit integer')
    print('  \\w : following eigth characters are converted into a little endian 32 bit integer')
    print('end of command \\x0A caracter is added at the end of each string')
    print('example:')
    print('> tobin.py r\\b30 u\\w34333231 \\b73 S | senda.bat')
    print('will send commands "r0", "u1234", "s" and "S" to tutorial application')
    
    


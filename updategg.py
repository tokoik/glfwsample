#!/usr/bin/python

funcs = []

with open('glext.h', 'r') as f:
	for line in f:
		s = line.split()
		if len(s) > 4 and s[0] == 'GLAPI':
			funcs.append(s[3])

with open('gg.h.inc', 'w') as f:
	for func in funcs:
		f.write('extern PFN' + func.upper() + 'PROC ' + func + ';\n')

with open('gg.cpp.inc', 'w') as f:
	for func in funcs:
		f.write('PFN' + func.upper() + 'PROC ' + func + ';\n')
	f.write('\n#define GGGETPROCADDRESS(func) func = glfwGetProcAddress(#func)\n')
	f.write('\nstatic inline void initGLExtFunc(void)\n{\n')
	for func in funcs:
		#f.write('  ' + func + ' = (PFN' + func.upper() + 'PROC)glfwGetProcAddress("' + func + '");\n')
		f.write('  GGGETPROCADDRESS(' + func + ');\n')
	f.write('}\n')

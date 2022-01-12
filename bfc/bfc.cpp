#include <iostream>
#include <fstream>
#include <streambuf>
#include <chrono>
#include <thread>
#include <string>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "[bfc] Invalid arguments." << std::endl;
		_Exit(1);
	}
	std::cout << "[bfc] BFC - A BrainF Compiler" << std::endl;
	std::cout << "[bfc] Loading " << argv[1] << "..." << std::endl;
	std::ifstream inprogfile(argv[1]);
	std::string str((std::istreambuf_iterator<char>(inprogfile)), std::istreambuf_iterator<char>());
	inprogfile.close();
	std::string s = "";
	int si = 1;
	std::string cp = "#include <iostream>\nint main(int argc, char *argv[]) {int memory[30000];for (int i = 0; i < 30000; i++) {memory[i] = 0;}int pointerindex = 0;";
	int instc = 0;
	int percent = 0;
	while (1) {
		s = "";
		int i = 0;
		// Parse
		char curinst = str[instc];
		switch (curinst) {
			case '+':
				cp += "memory[pointerindex]+=1;/*std::cout << \"Memory dump: \" << char(memory[pointerindex]) << std::endl;*/";
				break;
			case '-':
				cp += "memory[pointerindex]-=1;/*std::cout << \"Memory dump: \" << char(memory[pointerindex]) << std::endl;*/";
				break;
			case '.':
				cp += "std::cout << char(memory[pointerindex]);";
				break;
			case ',':
				break;
			case '<':
				cp += "pointerindex-=1;/*std::cout << \"Pointer Index moved to: \" << pointerindex << std::endl;*/";
				break;
			case '>':
				cp += "pointerindex+=1;/*std::cout << \"Pointer Index moved to: \" < pointerindex << std::endl;*/";
				break;
			case '[':
				cp += "while (memory[pointerindex] != 0){";
				break;
			case ']':
				cp += "}";
				break;
		}
		instc += 1;
		while (i < 3) {
			if (si < i) {
				s += " ";
			} else {
				s += ".";
			}
			if (curinst == '\n') {
				curinst = ' ';
			}
			std::cout << "[bfc] Parsing" << s << " " << curinst << " " << percent << "%\r";
			i += 1;
		}
		if (si > 2) {
			si = 0;
		} else {
			si += 1;
		}
		std::cout.flush();
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (instc + 1 > str.length()) {
			break;
		}
		percent = (double)(((double)instc / (double)str.length()) * 100);
	}
	cp += "}";
	std::cout << std::endl;
	std::cout << "[bfc] Done parsing." << std::endl;
	std::ofstream exf("executable.cpp");
	exf << cp;
	exf.close();
	std::cout << "[bfc] Compiling..." << std::endl;
	int res = std::system("clang++ -o executable executable.cpp");
	if (res/256 == 1) {
		std::cout << "[bfc] An error occured during compiling." << std::endl;
		res = std::system("rm executable.cpp");
		_Exit(1);
	}
	std::cout << "[bfc] Done Compiling." << std::endl;
	std::cout << "[bfc] Executing..." << std::endl;
	res = std::system("./executable");
	std::cout << std::endl << "[bfc] Execution complete." << std::endl;
	//res = std::system("rm executable executable.cpp");
	return 0;
}
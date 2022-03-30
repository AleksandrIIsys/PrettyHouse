#include "Class.h"
#include "function.h"
#include <iterator>

int main() {
	int pos = 0;
	int ikey = 0;
	int wardpos = 1;
	drawHospital();
	while (true) {
		switch (AuthoWindow()) {
		case 1:
			MenuPatient();
			break;
		case 2:
			drawTablet();
			drawfunctionfortablet(wardpos, 0);
			while (true) {
				if (_kbhit()) {
					WriteInAllFile();
					ikey = _getch();
					if ((ikey == 72) && (pos > 0)) {
						pos--;
					}
					if ((ikey == 80) && (pos < 3)) {
						pos++;
					}
					if (pos == 0) {
						if ((ikey == 75) && (wardpos != 0)) {
							wardpos--;
							drawTablet();
						}
						if (ikey == 77) {
							wardpos++;
							drawTablet();
						}
					}
					drawfunctionfortablet(wardpos, pos);
					if ((ikey == 13) && (pos != 0)) {
						if (pos == 1) {
							InfoPanel(wardpos);
						}
						if (pos == 2) {
							EnterPanel(wardpos);
						}
						if (pos == 3) {
							break;
						}
						drawfunctionfortablet(wardpos, pos);
					}
				}

			}
			break;
		case 3:
			adminPanel();
			break;
		default:
			cout << endl << "NOT CORRECT USERNAME OR PASSWORD" << endl;
			system("pause");
		}
	}

}


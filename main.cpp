#include <iostream>
#include "CommandProcessor.h"
using namespace std;

int main() {
    int command;

    cout << "\nAll commands:\n1-enter new text.\n2-start the new line.\n3-saving the information to your file."
            "\n4-loading the information from your file.\n5-print the current text to console.\n6-insert the text "
            "by line and symbol index.\n7-search by word.\n8-delete command.\n9-undo command.\n10-redo command."
            "\n11-cut command.\n12-paste command.\n13-copy command.\n14-replacement command.\n15-cursor logic."
            "\n16-encrypt.\n17-decrypt.\n";

    CommandProcessor cp;

    while (true) {
        cout << "\nChoose the command: ";
        cin >> command;
        switch (command) {
            case 1:
                cp.append();
                break;
            case 2:
                cp.newLine();

                break;
            case 3:
                cp.saveFile();
                break;
            case 4:
                cp.loadFile();
                break;
            case 5:
                cp.printText();
                break;
            case 6:
                cp.insert();
                break;
            case 7:
                cp.search();
                break;
            case 8:
                cp.deletet();
                break;
            case 9:
                cp.undo();
                break;
            case 10:
                cp.redo();
                break;
            case 11:
                cp.cut();
                break;
            case 12:
                cp.paste();
                break;
            case 13:
                cp.copy();
                break;
            case 14:
                cp.paste();
                break;
            case 15:
                cp.cursor();
                break;
            case 16:
                cp.encrypt();
                break;
            case 17:
                cp.decrypt();
                break;
            default:
                cout << "The command is not implemented.\n";
                break;
        }
    }
}
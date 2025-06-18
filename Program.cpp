#include "Form1.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    TypingTrainer::Form1 form;
    Application::Run(%form);
    return 0;
}
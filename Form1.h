#pragma once

// CLR ����� ����
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Windows.Forms.DataVisualization.dll>
#using <System.Drawing.dll>

#include <msclr/marshal_cppstd.h>
#include "TypingSession.h"
#include "Analyzer.h"
#include "Trainer.h"
#include "FileManager.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Windows::Forms::DataVisualization::Charting;
using namespace msclr::interop;

namespace TypingTrainer {

    public ref class Form1 : public Form {
    public:
        Form1();
    protected:
        ~Form1();
    private:
        // ���� �ھ� ������ ����
        List<String^> ^ pendingWords;     // ��Ÿ �� �ܾ� ��� ����Ʈ
        List<String^> ^ references;      // ������ ���� Ǯ
        Random ^ rnd;             // ���� ���� �̱�        
        TypingSession* session;
        List<int>^ errorCounts;    // ��ġ�� ���� ī��Ʈ
        List<double>^ speedIntervals; // �Է� �ӵ� ���
        String^ referenceText;  // ���� ���� ����

        // ���� UI ��Ʈ�� ����
        Label^ lblReference;
        TextBox^ txtInput;
        Label^ lblWarning;
        Button^ btnAnalyze;
        Button^ btnTrain;
        Button^ btnSave;
        Button^ btnLoad;
        ListBox^ lstTraining;
        Chart^ chartAccuracy;
        Chart^ chartBackspace;
        Chart^ chartSpeed;
        Panel^ pnlHeatmap;
        OpenFileDialog^ dlgOpen;
        SaveFileDialog^ dlgSave;
        System::ComponentModel::Container^ components;

        // ���� �ʱ�ȭ & �̺�Ʈ �ڵ鷯 ����
        void NextSentence();
        void InitializeComponent();
        void Form1_FormClosing(Object^, FormClosingEventArgs^);
        void txtInput_TextChanged(Object^, EventArgs^);
        void txtInput_KeyPress(Object^, KeyPressEventArgs^);
        void btnAnalyze_Click(Object^, EventArgs^);
        void btnTrain_Click(Object^, EventArgs^);
        void btnSave_Click(Object^, EventArgs^);
        void btnLoad_Click(Object^, EventArgs^);
        void pnlHeatmap_Paint(Object^, PaintEventArgs^);
        void lstTraining_SelectedIndexChanged(Object^, EventArgs^);
    };
}

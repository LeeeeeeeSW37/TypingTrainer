#pragma once

// CLR 어셈블리 참조
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
        // ── 코어 데이터 ──
        List<String^> ^ pendingWords;     // 오타 난 단어 대기 리스트
        List<String^> ^ references;      // 연습할 문장 풀
        Random ^ rnd;             // 랜덤 문장 뽑기        
        TypingSession* session;
        List<int>^ errorCounts;    // 위치별 에러 카운트
        List<double>^ speedIntervals; // 입력 속도 기록
        String^ referenceText;  // 현재 연습 문장

        // ── UI 컨트롤 ──
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

        // ── 초기화 & 이벤트 핸들러 ──
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

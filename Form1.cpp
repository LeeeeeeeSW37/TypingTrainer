// Form1.cpp
#include "Form1.h"
#include <msclr/marshal_cppstd.h>
#include <algorithm>    // std::max
#include <vector>       // std::vector
#include <msclr/marshal.h> // marshal_context


using namespace msclr::interop;
using namespace TypingTrainer;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Windows::Forms::DataVisualization::Charting;

Form1::Form1()
    : session(nullptr),
    references(gcnew List<String^>()),
    rnd(gcnew Random()),
    pendingWords(gcnew List<String^>()),
    errorCounts(gcnew List<int>()),
    speedIntervals(gcnew List<double>()),
    referenceText("")
{
    InitializeComponent();
    this->KeyPreview = true;
    array<String^>^ arr = gcnew array<String^> {
        L"Actions speak louder than words",
            L"A journey of a thousand miles begins with a single step",
            L"A picture is worth a thousand words",
            L"A watched pot never boils",
            L"All good things must come to an end",
            L"All that glitters is not gold",
            L"An apple a day keeps the doctor away",
            L"Beauty is in the eye of the beholder",
            L"Better late than never",
            L"Better safe than sorry",
            L"Birds of a feather flock together",
            L"Blood is thicker than water",
            L"Don't bite the hand that feeds you",
            L"Don't count your chickens before they hatch",
            L"Don't put all your eggs in one basket",
            L"Don't cross the bridge until you come to it",
            L"Don't judge a book by its cover",
            L"Don't look a gift horse in the mouth",
            L"Don't put off until tomorrow what you can do today",
            L"Don't throw the baby out with the bathwater",
            L"Easy come, easy go",
            L"Every cloud has a silver lining",
            L"Every dog has its day",
            L"Failing to plan is planning to fail",
            L"Familiarity breeds contempt",
            L"Fortune favors the bold",
            L"Good fences make good neighbors",
            L"Good things come in small packages",
            L"Good things come to those who wait",
            L"Great minds think alike",
            L"Haste makes waste",
            L"If it ain't broke, don't fix it",
            L"If you can't beat them, join them",
            L"If you can't stand the heat, get out of the kitchen",
            L"Ignorance is bliss",
            L"It's better to give than to receive",
            L"Keep your friends close and your enemies closer",
            L"Knowledge is power",
            L"Laughter is the best medicine",
            L"Let sleeping dogs lie",
            L"Look before you leap",
            L"Make hay while the sun shines",
            L"Measure twice, cut once",
            L"Money doesn't grow on trees",
            L"Necessity is the mother of invention",
            L"No man is an island",
            L"No pain, no gain",
            L"No rest for the wicked",
            L"No use crying over spilt milk",
            L"Nothing ventured, nothing gained",
            L"Old habits die hard",
            L"One man's trash is another man's treasure",
            L"Opportunity knocks but once",
            L"Out of sight, out of mind",
            L"Patience is a virtue",
            L"People who live in glass houses shouldn't throw stones",
            L"Practice makes perfect",
            L"Prevention is better than cure",
            L"Rome wasn't built in a day",
            L"Scratch my back and I'll scratch yours",
            L"Slow and steady wins the race",
            L"Strike while the iron is hot",
            L"The best defense is a good offense",
            L"The best things in life are free",
            L"The early bird catches the worm",
            L"The grass is always greener on the other side",
            L"The pen is mightier than the sword",
            L"Time and tide wait for no man",
            L"Too many cooks spoil the broth",
            L"Two heads are better than one",
            L"United we stand, divided we fall",
            L"Variety is the spice of life",
            L"Waste not, want not",
            L"Where there's smoke, there's fire",
            L"Where there's a will, there's a way",
            L"You can lead a horse to water, but you can't make him drink",
            L"You can't have your cake and eat it too",
            L"You can't make an omelet without breaking eggs",
            L"You can't teach an old dog new tricks",
            L"You reap what you sow",
            L"Half a loaf is better than none",
            L"A chain is only as strong as its weakest link",
            L"A rolling stone gathers no moss",
            L"A stitch in time saves nine",
            L"The more, the merrier",
            L"There's no such thing as a free lunch",
            L"Those who live by the sword die by the sword",
            L"A fool and his money are soon parted",
            L"The customer is always right",
            L"Good fences make good neighbors"
    };

    // ─── ② List<String^>에 담고 랜덤 준비 ───
    references = gcnew List<String^>(arr);

    // ─── ③ 연습 문장 랜덤 선택 ───
    int idx = rnd->Next(references->Count);
    referenceText = references[idx];
    lblReference->Text = referenceText;

    // ─── ④ TypingSession 초기화 ───
    marshal_context ctx;
    session = new TypingSession(ctx.marshal_as<std::string>(referenceText));
}

Form1::~Form1() {
    delete session;
    if (components) delete components;
}

void Form1::InitializeComponent() {
    pendingWords = gcnew List<String^>();
    components = gcnew System::ComponentModel::Container();
    lblReference = gcnew Label();
    txtInput = gcnew TextBox();
    lblWarning = gcnew Label();
    btnAnalyze = gcnew Button();
    btnTrain = gcnew Button();
    btnSave = gcnew Button();
    btnLoad = gcnew Button();
    lstTraining = gcnew ListBox();
    chartAccuracy = gcnew Chart();
    chartBackspace = gcnew Chart();
    chartSpeed = gcnew Chart();
    pnlHeatmap = gcnew Panel();
    dlgOpen = gcnew OpenFileDialog();
    dlgSave = gcnew SaveFileDialog();

    // Form properties
    this->Text = L"Typing Trainer";
    this->ClientSize = Drawing::Size(900, 740);
    this->FormClosing += gcnew FormClosingEventHandler(this, &Form1::Form1_FormClosing);

    // Reference Label
    lblReference->AutoSize = true;
    lblReference->Location = Point(10, 10);
    lblReference->Text = referenceText;

    // Input TextBox
    txtInput->Location = Point(10, 40);
    txtInput->Size = Drawing::Size(620, 25);
    txtInput->KeyPress += gcnew KeyPressEventHandler(this, &Form1::txtInput_KeyPress);
    txtInput->TextChanged += gcnew EventHandler(this, &Form1::txtInput_TextChanged);

    // Warning Label
    lblWarning->AutoSize = true;
    lblWarning->ForeColor = Color::Red;
    lblWarning->Location = Point(10, 70);

    // Analyze Button
    btnAnalyze->Text = L"Analyze";
    btnAnalyze->Location = Point(10, 100);
    btnAnalyze->Size = Drawing::Size(100, 30);
    btnAnalyze->Enabled = false;
    btnAnalyze->Click += gcnew EventHandler(this, &Form1::btnAnalyze_Click);

    // Train Button
    btnTrain->Text = L"Train";
    btnTrain->Location = Point(120, 100);
    btnTrain->Size = Drawing::Size(120, 30);
    btnTrain->Enabled = false;
    btnTrain->Click += gcnew EventHandler(this, &Form1::btnTrain_Click);

    // Save Button
    btnSave->Text = L"Save";
    btnSave->Location = Point(250, 100);
    btnSave->Size = Drawing::Size(100, 30);
    btnSave->Click += gcnew EventHandler(this, &Form1::btnSave_Click);

    // Load Button
    btnLoad->Text = L"Load";
    btnLoad->Location = Point(380, 100);
    btnLoad->Size = Drawing::Size(100, 30);
    btnLoad->Click += gcnew EventHandler(this, &Form1::btnLoad_Click);

    // Dialog Filters
    dlgOpen->Filter = L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*";
    dlgSave->Filter = L"Text Files (*.txt)|*.txt";

    // Charts
    // Accuracy Pie
    {
        ChartArea^ ca = gcnew ChartArea("AccArea");
        chartAccuracy->ChartAreas->Add(ca);
        Series^ s = gcnew Series("Accuracy");
        s->ChartType = SeriesChartType::Pie;
        s->IsValueShownAsLabel = true;
        chartAccuracy->Series->Add(s);
        chartAccuracy->Legends->Add(gcnew Legend("AccLegend"));
        chartAccuracy->Location = Point(10, 150);
        chartAccuracy->Size = Drawing::Size(300, 300);
    }
    // Backspace Column
    {
        ChartArea^ ca = gcnew ChartArea("BsArea");
        chartBackspace->ChartAreas->Add(ca);
        Series^ s = gcnew Series("Backspaces");
        s->ChartType = SeriesChartType::Column;
        s->IsValueShownAsLabel = true;
        chartBackspace->Series->Add(s);
        chartBackspace->Legends->Add(gcnew Legend("BsLegend"));
        chartBackspace->Location = Point(330, 150);
        chartBackspace->Size = Drawing::Size(300, 300);
    }
    // Speed Line
    {
        ChartArea^ ca = gcnew ChartArea("SpArea");
        chartSpeed->ChartAreas->Add(ca);
        Series^ s = gcnew Series("Speed");
        s->ChartType = SeriesChartType::Line;
        s->XValueType = ChartValueType::Int32;
        chartSpeed->Series->Add(s);
        chartSpeed->Legends->Add(gcnew Legend("SpLegend"));
        chartSpeed->Location = Point(10, 460);
        chartSpeed->Size = Drawing::Size(620, 200);
    }

    // Heatmap Panel
    pnlHeatmap->Location = Point(10, 680);
    pnlHeatmap->Size = Drawing::Size(620, 50);
    pnlHeatmap->BorderStyle = BorderStyle::FixedSingle;
    pnlHeatmap->Paint += gcnew PaintEventHandler(this, &Form1::pnlHeatmap_Paint);

    // ─── ListBox for training sentences ───
    lstTraining = gcnew ListBox();
    // 예: 오른쪽에 세로로 배치
    lstTraining->Location = Point(650, 150);
    lstTraining->Size = Drawing::Size(200, 560);
    // ListBox 생성·위치·크기 설정 뒤에
    lstTraining->SelectedIndexChanged +=
        gcnew EventHandler(this, &Form1::lstTraining_SelectedIndexChanged);



    // Add all controls
    this->Controls->AddRange(gcnew cli::array<Control^> {
        lblReference, txtInput, lblWarning,
            btnAnalyze, btnTrain, btnSave, btnLoad,
            chartAccuracy, chartBackspace, chartSpeed,
            pnlHeatmap, lstTraining

    });

}

void Form1::NextSentence() {
    txtInput->Clear();
    txtInput->Focus();
    // 1) 입력창·버튼 초기화
    btnAnalyze->Enabled = false;
    btnTrain->Enabled = false;

    // 2) 차트 초기화
    chartAccuracy->Series["Accuracy"]->Points->Clear();
    chartBackspace->Series["Backspaces"]->Points->Clear();
    chartSpeed->Series["Speed"]->Points->Clear();
    pnlHeatmap->Invalidate();

    // 3) 다음 문장 랜덤 선택
    int nextIdx = rnd->Next(references->Count);
    referenceText = references[nextIdx];
    lblReference->Text = referenceText;

    // 4) 세션 재초기화
    delete session;
    marshal_context ctx;
    session = new TypingSession(ctx.marshal_as<std::string>(referenceText));

    // 5) pendingWords 초기화
    pendingWords->Clear();
    lstTraining->Items->Clear();

    // 6) 속도·오류 카운트 초기화
    speedIntervals->Clear();
    errorCounts->Clear();
    for (int i = 0; i < referenceText->Length; ++i)
        errorCounts->Add(0);
}

void Form1::Form1_FormClosing(Object^ sender, FormClosingEventArgs^ e) {
    marshal_context ctx;
    std::string path = ctx.marshal_as<std::string>(Path::Combine(Application::StartupPath, "autosave_session.txt"));
    FileManager::saveSession(*session, path);
}

void Form1::txtInput_TextChanged(Object^ sender, EventArgs^ e)
{
    // 사용자가 입력한 현재 텍스트 (양쪽 공백 제거)
    String^ current = txtInput->Text->Trim();

    // Analyze 버튼 활성화 조건
    btnAnalyze->Enabled = (txtInput->TextLength >= referenceText->Length);
    lblWarning->Text = L"";

    // ─── 1) 훈련 모드 (pendingWords에 남은 단어가 있을 때) ───
// Form1.cpp, txtInput_TextChanged 안
    if (pendingWords->Count > 0)
    {
        String^ current = txtInput->Text->Trim();
        if (pendingWords->Contains(current))
        {
            // 1) pendingWords 에서 제거
            pendingWords->Remove(current);

            // 2) 리스트박스 갱신
            lstTraining->Items->Clear();
            for each (String ^ w in pendingWords)
                lstTraining->Items->Add(w);

            // 3) 입력창 클리어
            txtInput->Text = "";
            txtInput->Focus();

            // 4) 이제 pendingWords 비어 있으면
            if (pendingWords->Count == 0)
            {
                // ▷ 리스트박스 완전 비우기 (이 한 줄이 빠졌다면 마지막 단어가 남습니다)
                lstTraining->Items->Clear();
            }
        }
        return;
    }
// ─── 2) 풀 문장 모드 (pendingWords 비어 있을 때) ───
// txtInput_TextChanged 의 풀 문장 모드 부분
    if (pendingWords->Count == 0 && txtInput->Text->Equals(referenceText, StringComparison::Ordinal))
    {
        // 1) 입력창 클리어
        txtInput->Text = "";
        txtInput->Focus();

        // 2) 리스트박스도 초기화
        lstTraining->Items->Clear();

        // 3) 다음 문장 랜덤 인덱스 생성 (여기서 int nextIdx 선언!)
        int nextIdx = rnd->Next(references->Count);

        // 4) referenceText 갱신 및 화면에 표시
        referenceText = references[nextIdx];
        lblReference->Text = referenceText;

        // 5) 세션 재초기화
        delete session;
        marshal_context ctx;

        session = new TypingSession(
            ctx.marshal_as<std::string>(referenceText)
        );

        // 6) 기타 UI 초기화
        speedIntervals->Clear();
        // pendingWords 는 이미 비어 있으니 따로 건드릴 필요 없음
    }
}


void Form1::txtInput_KeyPress(Object^ sender, KeyPressEventArgs^ e) {
    char ch = static_cast<char>(e->KeyChar);
    bool isBS = (e->KeyChar == '\b');
    if (isBS || ch == ' ' || ch == '\''||"," || std::isalpha(static_cast<unsigned char>(ch))) {
        session->addEvent(ch, isBS);
        lblWarning->Text = L"";
    }
    else {
        e->Handled = true;
        lblWarning->Text = L"Only letters and spaces allowed.";
    }
}

void Form1::btnAnalyze_Click(Object^ sender, EventArgs^ e) {
    AnalysisResult res = Analyzer::analyze(*session);

    // Update Accuracy pie
    auto pie = chartAccuracy->Series["Accuracy"];
    pie->Points->Clear();
    pie->Points->AddXY("Correct", res.accuracy * 100);
    pie->Points->AddXY("Error", (1 - res.accuracy) * 100);

    // Update Backspaces
    auto col = chartBackspace->Series["Backspaces"];
    col->Points->Clear();
    for each (auto kv in res.backspaceStats) {
        String^ lbl = (kv.first == '\b')
            ? L"BS"
            : gcnew String((wchar_t)kv.first, 1);
        col->Points->AddXY(lbl, kv.second);
    }

    // Update Speed line
    speedIntervals->Clear();
    for each (double dt in res.intervalsMs)
        speedIntervals->Add(dt);
    auto line = chartSpeed->Series["Speed"];
    line->Points->Clear();
    for (int i = 0; i < speedIntervals->Count; ++i)
        line->Points->AddXY(i + 1, speedIntervals[i]);

    // Initialize errorCounts
    int count = referenceText->Length;
    errorCounts->Clear();
    for (int i = 0; i < count; ++i) errorCounts->Add(0);
    for each (int p in res.errorPositions)
        if (p >= 0 && p < count)
            errorCounts[p] += 1;

    // Redraw heatmap
    pnlHeatmap->Invalidate();

    if (pendingWords->Count == 0 && res.accuracy >= 1.0) {
        MessageBox::Show(
            L"Perfect! Moving to next sentence.",
            L"Next!",
            MessageBoxButtons::OK,
            MessageBoxIcon::Information
        );
        NextSentence();
        return;
    }

    // ───errorPositions → pendingWords 로 변환 ───
    marshal_context ctx;
    auto words = Trainer::generateTrainingSentences(res.errorPositions,
        ctx.marshal_as<std::string>(referenceText));
    for each (auto& w in words) {
        String^ sw = gcnew String(w.c_str());
        if (!pendingWords->Contains(sw))
            pendingWords->Add(sw);
    }

    // ─── 리스트박스 갱신 ───
    lstTraining->Items->Clear();
    for each (auto sw in pendingWords)
        lstTraining->Items->Add(sw);

    btnTrain->Enabled = pendingWords->Count > 0;

}

void Form1::btnTrain_Click(Object^ sender, EventArgs^ e) {
    std::vector<int> errs;
    for each (int cnt in errorCounts)
        errs.push_back(cnt);
    marshal_context ctx;
    std::string refStr = ctx.marshal_as<std::string>(referenceText);
    auto sentences = Trainer::generateTrainingSentences(errs, refStr);

    lstTraining->Items->Clear();
    for each (auto& s in sentences)
        lstTraining->Items->Add(gcnew String(s.c_str()));

}

void Form1::btnSave_Click(Object^ sender, EventArgs^ e) {
    if (dlgSave->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        marshal_context ctx;
        std::string path = ctx.marshal_as<std::string>(dlgSave->FileName);
        FileManager::saveSession(*session, path);
    }
}

void Form1::btnLoad_Click(Object^ sender, EventArgs^ e) {
    if (dlgOpen->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        marshal_context ctx;
        std::string path = ctx.marshal_as<std::string>(dlgOpen->FileName);
        TypingSession loaded = FileManager::loadSession(path);
        delete session;
        session = new TypingSession(loaded.getReferenceText());
        for (auto& ev : loaded.getEvents())
            session->addEvent(ev.character, ev.isBackspace);
        // Reset UI
        txtInput->Text = "";
        lblWarning->Text = L"";
        btnAnalyze->Enabled = false;
        btnTrain->Enabled = false;
        chartAccuracy->Series["Accuracy"]->Points->Clear();
        chartBackspace->Series["Backspaces"]->Points->Clear();
        chartSpeed->Series["Speed"]->Points->Clear();
        pnlHeatmap->Invalidate();
    }
}

void Form1::pnlHeatmap_Paint(Object^ sender, PaintEventArgs^ e) {
    int count = referenceText->Length;
    if (count == 0) return;
    int maxErr = 0;
    for each (int cnt in errorCounts)
        maxErr = std::max<int>(maxErr, cnt);
    int w = pnlHeatmap->Width / count;
    for (int i = 0; i < count; ++i) {
        int intensity = (maxErr > 0) ? (255 * errorCounts[i] / maxErr) : 0;
        Color fillColor = Color::FromArgb(255, intensity, 0, 0);
        Drawing::Rectangle rect(i * w, 0, w, pnlHeatmap->Height);
        e->Graphics->FillRectangle(gcnew SolidBrush(fillColor), rect);
        e->Graphics->DrawRectangle(Pens::Black, rect);
    }

}
void Form1::lstTraining_SelectedIndexChanged(Object^ sender, EventArgs^ e) {
    txtInput->Text = "";
    txtInput->Focus();
    // 1) 선택된 아이템을 String^ 타입으로 꺼냅니다.
    String^ sel = safe_cast<String^>(lstTraining->SelectedItem);
    if (sel == nullptr) return;

    // 2) referenceText와 라벨 갱신
    referenceText = sel;
    lblReference->Text = referenceText;

    // 3) 입력창 및 경고 초기화
    txtInput->Text = "";
    lblWarning->Text = "";

    // 4) 내부 세션 재생성
    delete session;
    msclr::interop::marshal_context ctx;
    std::string nativeRef = ctx.marshal_as<std::string>(referenceText);
    session = new TypingSession(nativeRef);

    // 5) 차트·히트맵·버튼 초기화
    errorCounts->Clear();
    speedIntervals->Clear();

    chartAccuracy->Series["Accuracy"]->Points->Clear();
    chartBackspace->Series["Backspaces"]->Points->Clear();
    chartSpeed->Series["Speed"]->Points->Clear();
    pnlHeatmap->Invalidate();

    btnAnalyze->Enabled = false;
    btnTrain->Enabled = false;
}
#include "EasyVideoEditor.h"

EasyVideoEditor::EasyVideoEditor(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Widgets::getInstance()->initWidgets(this);

    ////// Init ui.
    ui.edt_coloremphasis_red->setValidator(new QIntValidator(0, 255, this));
    ui.edt_coloremphasis_green->setValidator(new QIntValidator(0, 255, this));
    ui.edt_coloremphasis_blue->setValidator(new QIntValidator(0, 255, this));
    ui.sd_coloremphasis_red->setStyleSheet("QSlider::handle:horizontal {background: red;} ");
    ui.sd_coloremphasis_green->setStyleSheet("QSlider::handle:horizontal {background: green;} ");
    ui.sd_coloremphasis_blue->setStyleSheet("QSlider::handle:horizontal {background: blue;} ");
    ui.sd_changebrightness_brightness->setStyleSheet("QSlider::handle:horizontal {background: yellow;} ");

    ////// Init data.
    new SideMenu(ui.btn_coloremphasis, ui.w_coloremphasis);
    new SideMenu(ui.btn_changebrightness, ui.w_changebrightness);
    new SideMenu(ui.btn_changecontrast, ui.w_changecontrast);
    new SideMenu(ui.btn_filter, ui.w_filter);
    new SideMenu(ui.btn_chromakey, ui.w_chromakey);
    new SideMenu(ui.btn_transition, ui.w_transition);
    new SideMenu(ui.btn_addimage, ui.w_addimage);
    new SideMenu(ui.btn_addvideo, ui.w_addvideo);
    new SideMenu(ui.btn_cutvideo, ui.w_cutvideo);
    new SideMenu(ui.btn_resize, ui.w_resize);
    new SideMenu(ui.btn_changeplayspeed, ui.w_changeplayspeed);
    new SideMenu(ui.btn_addsubtitle, ui.w_addsubtitle);
    SideMenu::selectSideMenu(ui.btn_coloremphasis);

    ////// Init signal, slot.
    connect(ui.btn_coloremphasis, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_changebrightness, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_changecontrast, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_filter, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_chromakey, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_transition, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_addimage, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_addvideo, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_cutvideo, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_resize, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_changeplayspeed, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_addsubtitle, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));

    // Connect apply button.
    connect(ui.btn_coloremphasis_apply, SIGNAL(clicked()), this, SLOT(colorEmphasisApplyButtonClicked()));
    connect(ui.btn_changebrightness_apply, SIGNAL(clicked()), this, SLOT(changeBrightnessApplyButtonClicked()));
    connect(ui.btn_changecontrast_apply, SIGNAL(clicked()), this, SLOT(changeContrastApplyButtonClicked()));
    connect(ui.btn_filter_apply, SIGNAL(clicked()), this, SLOT(filterApplyButtonClicked()));
    connect(ui.btn_chromakey_apply, SIGNAL(clicked()), this, SLOT(chromakeyApplyButtonClicked()));
    connect(ui.btn_transition_apply, SIGNAL(clicked()), this, SLOT(transitionApplyButtonClicked()));
    connect(ui.btn_addimage_apply, SIGNAL(clicked()), this, SLOT(addImageApplyButtonClicked()));
    connect(ui.btn_addvideo_apply, SIGNAL(clicked()), this, SLOT(addVideoApplyButtonClicked()));
    connect(ui.btn_cutvideo_apply, SIGNAL(clicked()), this, SLOT(cutVideoApplyButtonClicked()));
    connect(ui.btn_resize_apply, SIGNAL(clicked()), this, SLOT(resizeApplyButtonClicked()));
    connect(ui.btn_changeplayspeed_apply, SIGNAL(clicked()), this, SLOT(changePlaySpeedButtonClicked()));
    connect(ui.btn_addsubtitle_apply, SIGNAL(clicked()), this, SLOT(addSubtitleButtonClicked()));

    // Connect slider <-> line edit.
    connect(ui.sd_coloremphasis_red, SIGNAL(valueChanged(int)), this, SLOT(setLineEditBySlider(int)));
    connect(ui.sd_coloremphasis_green, SIGNAL(valueChanged(int)), this, SLOT(setLineEditBySlider(int)));
    connect(ui.sd_coloremphasis_blue, SIGNAL(valueChanged(int)), this, SLOT(setLineEditBySlider(int)));;
    connect(ui.edt_coloremphasis_red, SIGNAL(textChanged(QString)), this, SLOT(setSliderByLineEdit(QString)));;
    connect(ui.edt_coloremphasis_green, SIGNAL(textChanged(QString)), this, SLOT(setSliderByLineEdit(QString)));
    connect(ui.edt_coloremphasis_blue, SIGNAL(textChanged(QString)), this, SLOT(setSliderByLineEdit(QString)));
    connect(ui.sd_changebrightness_brightness, SIGNAL(valueChanged(int)), this, SLOT(setLineEditBySlider(int)));;
    connect(ui.edt_changebrightness_brightness, SIGNAL(textChanged(QString)), this, SLOT(setSliderByLineEdit(QString)));
    connect(ui.sd_changecontrast_contrast, SIGNAL(valueChanged(int)), this, SLOT(setLineEditBySlider(int)));;
    connect(ui.edt_changecontrast_contrast, SIGNAL(textChanged(QString)), this, SLOT(setSliderByLineEdit(QString)));
    connect(ui.sd_filter_clarity, SIGNAL(valueChanged(int)), this, SLOT(setLineEditBySlider(int)));;
    connect(ui.edt_filter_clarity, SIGNAL(textChanged(QString)), this, SLOT(setSliderByLineEdit(QString)));
}

EasyVideoEditor::~EasyVideoEditor()
{}

QString EasyVideoEditor::kor(std::string korString) {
    return QString::fromLocal8Bit(korString);
}

void EasyVideoEditor::workAfterMainWindowShowed() {
    QString baseVideoPath = QFileDialog::getOpenFileName(this, "Select video files to edit", QDir::homePath(), tr("Video Files (*.mp4 *.avi *.wmv *.mov)"));
    if (!baseVideoPath.isEmpty()) {
        EveProject::getInstance()->addVideo(new Video(0, baseVideoPath.toStdString()));
    }
}

bool EasyVideoEditor::event(QEvent* event) {
    const bool ret_val = QMainWindow::event(event);
    if (!workAfterMainWindowShowedCalled && event->type() == QEvent::Paint) {
        workAfterMainWindowShowedCalled = true;
        workAfterMainWindowShowed();
    }

    return ret_val;
}

void EasyVideoEditor::sideMenuClicked() {
    SideMenu::selectSideMenu((QPushButton*)sender());
}

void EasyVideoEditor::setLineEditBySlider(int value) {
    QObject* senderObject = sender();
    if (senderObject == ui.sd_coloremphasis_red) ui.edt_coloremphasis_red->setText(QString::number(value));
    else if (senderObject == ui.sd_coloremphasis_green) ui.edt_coloremphasis_green->setText(QString::number(value));
    else if (senderObject == ui.sd_coloremphasis_blue) ui.edt_coloremphasis_blue->setText(QString::number(value));
    else if (senderObject == ui.sd_changebrightness_brightness) ui.edt_changebrightness_brightness->setText(QString::number(value));
    else if (senderObject == ui.sd_changecontrast_contrast) ui.edt_changecontrast_contrast->setText(QString::number(value));
    else if (senderObject == ui.sd_filter_clarity) ui.edt_filter_clarity->setText(QString::number(value));
}

void EasyVideoEditor::setSliderByLineEdit(QString value) {
    QObject* senderObject = sender();
    if (senderObject == ui.edt_coloremphasis_red) ui.sd_coloremphasis_red->setValue(value.toInt());
    else if (senderObject == ui.edt_coloremphasis_green) ui.sd_coloremphasis_green->setValue(value.toInt());
    else if (senderObject == ui.edt_coloremphasis_blue) ui.sd_coloremphasis_blue->setValue(value.toInt());
    else if (senderObject == ui.edt_changebrightness_brightness) ui.sd_changebrightness_brightness->setValue(value.toInt());
    else if (senderObject == ui.edt_changecontrast_contrast) ui.sd_changecontrast_contrast->setValue(value.toInt());
    else if (senderObject == ui.edt_filter_clarity) ui.sd_filter_clarity->setValue(value.toInt());
}

void EasyVideoEditor::colorEmphasisApplyButtonClicked() {
    if (EveProject::getInstance()->getCurrentFrameNumber() != -1) { // If there is more than one frame.
        ColorEmphasis* colorEmphasis = new ColorEmphasis(
            ui.edt_coloremphasis_red->text().toInt(),
            ui.edt_coloremphasis_green->text().toInt(),
            ui.edt_coloremphasis_blue->text().toInt()
        );

        if (ui.rbtn_coloremphasis_currentframe->isChecked()) {
            EveProject::getInstance()->getCurrentFrame()->addCommand(colorEmphasis);
        }
        else if (ui.rbtn_coloremphasis_allframe->isChecked()) {
            std::vector<Frame*>* allFrames = EveProject::getInstance()->getFrameList();
            for (int loop = 0; loop < allFrames->size(); loop++) {
                allFrames->at(loop)->addCommand(colorEmphasis);
            }
        }
        else if (ui.rbtn_coloremphasis_rangeframe->isChecked()) {
            int startIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(ui.edt_coloremphasls_rangestart->text()));
            int endIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(ui.edt_coloremphasis_rangeend->text()));
            for (int loop = startIndex; loop < endIndex; loop++) {
                EveProject::getInstance()->getFrameByIndex(loop)->addCommand(colorEmphasis);
            }
        }
    }
};

void EasyVideoEditor::changeBrightnessApplyButtonClicked() {};

void EasyVideoEditor::changeContrastApplyButtonClicked() {};

void EasyVideoEditor::filterApplyButtonClicked() {};

void EasyVideoEditor::chromakeyApplyButtonClicked() {};

void EasyVideoEditor::transitionApplyButtonClicked() {};

void EasyVideoEditor::addImageApplyButtonClicked() {};

void EasyVideoEditor::addVideoApplyButtonClicked() {};

void EasyVideoEditor::cutVideoApplyButtonClicked() {};

void EasyVideoEditor::resizeApplyButtonClicked() {};

void EasyVideoEditor::changePlaySpeedButtonClicked() {};

void EasyVideoEditor::addSubtitleButtonClicked() {};
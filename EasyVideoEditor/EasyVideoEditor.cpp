#include "EasyVideoEditor.h"



int EasyVideoEditor::top = 0;
int EasyVideoEditor::down = 0;
int EasyVideoEditor::left = 0;
int EasyVideoEditor::right = 0;
EasyVideoEditor::Mode EasyVideoEditor::mode = EasyVideoEditor::Mode::MODE_EDIT;
QMutex EasyVideoEditor::mutex;
cv::Size EasyVideoEditor::resizeData;

EasyVideoEditor::EasyVideoEditor(QWidget* parent) : QMainWindow(parent){
    ui.setupUi(this);
    Widgets::getInstance()->initWidgets(this);

    ////// Init ui.
    ui.btn_pause->setVisible(false);
    ui.w_contentarea->setEnabled(false);
    ui.w_videocontrolarea->setEnabled(false);
    ui.edt_coloremphasis_red->setValidator(new QIntValidator(0, 255, this));
    ui.edt_coloremphasis_green->setValidator(new QIntValidator(0, 255, this));
    ui.edt_coloremphasis_blue->setValidator(new QIntValidator(0, 255, this));
    ui.sd_coloremphasis_red->setStyleSheet("QSlider::handle:horizontal {background: red;} ");
    ui.sd_coloremphasis_green->setStyleSheet("QSlider::handle:horizontal {background: green;} ");
    ui.sd_coloremphasis_blue->setStyleSheet("QSlider::handle:horizontal {background: blue;} ");
    ui.sd_changebrightness_brightness->setStyleSheet("QSlider::handle:horizontal {background: yellow;} ");
    ui.cmbox_addsubtitle_font->addItem("SIMPLEX"); // FONT_HERSHEY_SIMPLEX
    ui.cmbox_addsubtitle_font->addItem("PLAIN"); // FONT_HERSHEY_PLAIN
    ui.cmbox_addsubtitle_font->addItem("DUPLEX"); // FONT_HERSHEY_DUPLEX
    ui.cmbox_addsubtitle_font->addItem("COMPLEX"); // FONT_HERSHEY_COMPLEX
    ui.cmbox_addsubtitle_font->addItem("COMPLEX_SMALL"); // FONT_HERSHEY_COMPLEX_SMALL
    ui.cmbox_addsubtitle_font->addItem("SCRIPT_SIMPLEX"); // FONT_HERSHEY_SCRIPT_SIMPLEX
    ui.cmbox_addsubtitle_font->addItem("SCRIPT_COMPLEX"); // FONT_HERSHEY_SCRIPT_COMPLEX
    ui.cmbox_addsubtitle_font->addItem("ITALIC"); // FONT_ITALIC

    ////// Init data.
    mode = Mode::MODE_EDIT;
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
    connect(ui.menu_newproject, SIGNAL(triggered()), this, SLOT(newProjectMenuClicked()));
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
    connect(ui.btn_play, SIGNAL(clicked()), this, SLOT(playButtonClicked()));
    connect(ui.btn_pause, SIGNAL(clicked()), this, SLOT(pauseButtonClicked()));
    connect(ui.btn_reset, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
    connect(ui.btn_forward5seconds, SIGNAL(clicked()), this, SLOT(forward5SecondsButtonclicked()));
    connect(ui.btn_backward5seconds, SIGNAL(clicked()), this, SLOT(backward5SecondsButtonClicked()));
    connect(ui.btn_addimage_select_path, SIGNAL(clicked()), this, SLOT(addImageSelectButtonClicked()));
    connect(ui.btn_addvideo_select_path, SIGNAL(clicked()), this, SLOT(addVideoSelectButtonClicked()));

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

void EasyVideoEditor::workAfterMainWindowShowed() {
    newProject();
}

void EasyVideoEditor::updateSampleFrame() {
    if (SideMenu::selectedSideMenu() == Command::CommandType::COLOR_EMPHASIS) {
        (*EveProject::getInstance()->getCurrentFrame()).copyTo(&editingFrame);
        ColorEmphasis colorEmphasis(false,
            ui.edt_coloremphasis_red->text().toInt(),
            ui.edt_coloremphasis_green->text().toInt(),
            ui.edt_coloremphasis_blue->text().toInt()
        );
        editingFrame.addCommand(&colorEmphasis);
        cv::Mat showFrame;
        editingFrame.getCommandAppliedFrameData(&showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
    }
    else if (SideMenu::selectedSideMenu() == Command::CommandType::CHANGE_BRIGHTNESS) {
        (*EveProject::getInstance()->getCurrentFrame()).copyTo(&editingFrame);
        ChangeBrightness changeBrightness(false,
            ui.edt_changebrightness_brightness->text().toInt()
        );
        editingFrame.addCommand(&changeBrightness);
        cv::Mat showFrame;
        editingFrame.getCommandAppliedFrameData(&showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
    }
    else if (SideMenu::selectedSideMenu() == Command::CommandType::CHANGE_CONTRAST) {
        (*EveProject::getInstance()->getCurrentFrame()).copyTo(&editingFrame);
        ChangeContrast changeContrast(false,
            ui.edt_changecontrast_contrast->text().toInt()
        );
        editingFrame.addCommand(&changeContrast);
        cv::Mat showFrame;
        editingFrame.getCommandAppliedFrameData(&showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
    }
}

void EasyVideoEditor::clear() {
    mutex.lock();
    // Init Data.
    mode = Mode::MODE_EDIT;
    editingFrame.removeAllCommand();

    // Init UI.
    ui.lbl_currentplaytime->setText("00:00:00.000");
    ui.lbl_maxplaytime->setText("00:00:00.000");
    ui.sd_videoprogress->setValue(0);
    ui.btn_play->setVisible(true);
    ui.btn_pause->setVisible(false);
    ui.w_contentarea->setEnabled(false);
    ui.w_sidemenuarea->setEnabled(false);
    ui.w_sidemenupagearea->setEnabled(false);
    ui.w_videocontrolarea->setEnabled(false);
    ui.w_videoarea->setStyleSheet("background-color:#000000;");

    EveProject::getInstance()->clear(this);

    mutex.unlock();
}

void EasyVideoEditor::newProject() {
    QString baseVideoPath = QFileDialog::getOpenFileName(this, "Select video file to edit", QDir::homePath(), tr("Video File (*.mp4 *.avi *.wmv *.mov)"));
    if (!baseVideoPath.isEmpty()) {
        clear();
        Video* baseVideo = new Video(0, baseVideoPath.toStdString());
        EveProject::getInstance()->addVideo(baseVideo);
        for (int loop = 0; loop < baseVideo->getFrameCount(); loop++) {
            EveProject::getInstance()->addFrame(new Frame(0, loop));
        }

        ui.w_contentarea->setEnabled(true);
        ui.w_sidemenuarea->setEnabled(true);
        ui.w_sidemenupagearea->setEnabled(true);
        ui.w_videocontrolarea->setEnabled(false);

        int originalWidth = EveProject::getInstance()->getBaseWidth();
        int originalHeight = EveProject::getInstance()->getBaseHeight();
        int showWidth = 960;
        int showHeight = 444;
        int convertedWidth;
        int convertedHeight;

        double h1 = showWidth * (originalHeight / (double)originalWidth);
        double w2 = showHeight * (originalWidth / (double)originalHeight);

        if (h1 < showHeight) {
            resizeData = cv::Size(showWidth, h1);
        }
        else {
            resizeData = cv::Size(w2, showHeight);
        }

        top = (showHeight - resizeData.height) / 2;
        down = (showHeight - resizeData.height + 1) / 2;
        left = (showWidth - resizeData.width) / 2;
        right = (showWidth - resizeData.width + 1) / 2;

        ui.lbl_maxplaytime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(EveProject::getInstance()->getFrameList()->size())));

        cv::Mat showFrame;
        EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(&showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
    }
}

void EasyVideoEditor::updateInformationArea() {

}

bool EasyVideoEditor::event(QEvent* e) {
    const bool ret_val = QMainWindow::event(e);
    if (!workAfterMainWindowShowedCalled && e->type() == QEvent::Paint) {
        workAfterMainWindowShowedCalled = true;
        workAfterMainWindowShowed();
    }

    return ret_val;
}

void EasyVideoEditor::keyPressEvent(QKeyEvent* e) {
    if ((e->key() == Qt::Key_E) && QApplication::keyboardModifiers() && Qt::ControlModifier) {
        mutex.lock();
        if (mode == Mode::MODE_EDIT) {
            mode = Mode::MODE_WATCH_PAUSE;
            ui.w_sidemenuarea->setEnabled(false);
            ui.w_sidemenupagearea->setEnabled(false);
            ui.w_videocontrolarea->setEnabled(true);
        }
        else {
            if (mode == Mode::MODE_WATCH_PLAY) {
                ui.btn_play->setVisible(true);
                ui.btn_pause->setVisible(false);
            }
            mode = Mode::MODE_EDIT;
            ui.w_sidemenuarea->setEnabled(true);
            ui.w_sidemenupagearea->setEnabled(true);
            ui.w_videocontrolarea->setEnabled(false);
        }
        mutex.unlock();
    }
}

void EasyVideoEditor::newProjectMenuClicked(){
    mutex.lock();
    if (mode == Mode::MODE_WATCH_PLAY) mode = Mode::MODE_WATCH_PAUSE;
    mutex.unlock();
    newProject();
}

void EasyVideoEditor::encodingToMp4MenuClicked(){
}

void EasyVideoEditor::encodingToAviMenuClicked(){
}

void EasyVideoEditor::encodingToWmvMenuClicked(){
}

void EasyVideoEditor::encodingToMovMenuClicked(){
}

void EasyVideoEditor::exitMenuClicked(){
}

void EasyVideoEditor::setLineEditBySlider(int value) {
    QObject* senderObject = sender();
    if (senderObject == ui.sd_coloremphasis_red) ui.edt_coloremphasis_red->setText(QString::number(value));
    else if (senderObject == ui.sd_coloremphasis_green) ui.edt_coloremphasis_green->setText(QString::number(value));
    else if (senderObject == ui.sd_coloremphasis_blue) ui.edt_coloremphasis_blue->setText(QString::number(value));
    else if (senderObject == ui.sd_changebrightness_brightness) ui.edt_changebrightness_brightness->setText(QString::number(value));
    else if (senderObject == ui.sd_changecontrast_contrast) ui.edt_changecontrast_contrast->setText(QString::number(value));
    else if (senderObject == ui.sd_filter_clarity) ui.edt_filter_clarity->setText(QString::number(value));

    updateSampleFrame();
}

void EasyVideoEditor::setSliderByLineEdit(QString value) {
    QObject* senderObject = sender();
    if (senderObject == ui.edt_coloremphasis_red) ui.sd_coloremphasis_red->setValue(value.toInt());
    else if (senderObject == ui.edt_coloremphasis_green) ui.sd_coloremphasis_green->setValue(value.toInt());
    else if (senderObject == ui.edt_coloremphasis_blue) ui.sd_coloremphasis_blue->setValue(value.toInt());
    else if (senderObject == ui.edt_changebrightness_brightness) ui.sd_changebrightness_brightness->setValue(value.toInt());
    else if (senderObject == ui.edt_changecontrast_contrast) ui.sd_changecontrast_contrast->setValue(value.toInt());
    else if (senderObject == ui.edt_filter_clarity) ui.sd_filter_clarity->setValue(value.toInt());

    updateSampleFrame();
}

void EasyVideoEditor::sideMenuClicked() {
    SideMenu::selectSideMenu((QPushButton*)sender());
}

void EasyVideoEditor::playButtonClicked() {
    mutex.lock();
    if (EveProject::getInstance()->getCurrentFrameNumber() == EveProject::getInstance()->getFrameList()->size() - 1)
        EveProject::getInstance()->setCurrentFrameNumber(0);
    mode = Mode::MODE_WATCH_PLAY;
    ui.btn_play->setVisible(false);
    ui.btn_pause->setVisible(true);
    mutex.unlock();
    PlayVideo* playVideo = new PlayVideo(this);
    playVideo->start();
}

void EasyVideoEditor::pauseButtonClicked() {
    mutex.lock();
    mode = Mode::MODE_WATCH_PAUSE;
    ui.btn_play->setVisible(true);
    ui.btn_pause->setVisible(false);
    mutex.unlock();
}

void EasyVideoEditor::resetButtonClicked() {
    mutex.lock();
    mode = Mode::MODE_WATCH_PAUSE;
    ui.btn_play->setVisible(true);
    ui.btn_pause->setVisible(false);
    ui.lbl_currentplaytime->setText("00:00:00.000");
    ui.sd_videoprogress->setValue(0);
    EveProject::getInstance()->setCurrentFrameNumber(0);
    cv::Mat showFrame;
    EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(&showFrame, true);
    UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
    mutex.unlock();
}

void EasyVideoEditor::forward5SecondsButtonclicked() {
    mutex.lock();
    EveProject::getInstance()->forward5Seconds();
    if (mode == Mode::MODE_WATCH_PAUSE) {
        int currentFrameIndex = EveProject::getInstance()->getCurrentFrameNumber();
        ui.lbl_currentplaytime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(currentFrameIndex)));
        ui.sd_videoprogress->setValue(currentFrameIndex);
        cv::Mat showFrame;
        EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(&showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
    }
    mutex.unlock();
}

void EasyVideoEditor::backward5SecondsButtonClicked() {
    mutex.lock();
    EveProject::getInstance()->backward5Seconds();
    if (mode == Mode::MODE_WATCH_PAUSE) {
        int currentFrameIndex = EveProject::getInstance()->getCurrentFrameNumber();
        ui.lbl_currentplaytime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(currentFrameIndex)));
        ui.sd_videoprogress->setValue(currentFrameIndex);
        cv::Mat showFrame;
        EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(&showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
    }
    mutex.unlock();
}

void EasyVideoEditor::colorEmphasisApplyButtonClicked() {
    if (EveProject::getInstance()->getCurrentFrameNumber() != -1) { // If there is more than one frame.
        QLineEdit* rangeStart = ui.edt_coloremphasis_rangestart;
        QLineEdit* rangeEnd = ui.edt_coloremphasis_rangeend;
        Command* command = new ColorEmphasis(true,
            ui.edt_coloremphasis_red->text().toInt(),
            ui.edt_coloremphasis_green->text().toInt(),
            ui.edt_coloremphasis_blue->text().toInt()
        );

        if (ui.rbtn_coloremphasis_currentframe->isChecked()) {
            EveProject::getInstance()->getCurrentFrame()->addCommand(command);
        }
        else if (ui.rbtn_coloremphasis_allframe->isChecked()) {
            std::vector<Frame*>* allFrames = EveProject::getInstance()->getFrameList();
            for (int loop = 0; loop < allFrames->size(); loop++) {
                allFrames->at(loop)->addCommand(command);
            }
        }
        else if (ui.rbtn_coloremphasis_rangeframe->isChecked()) {
            int startIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeStart->text()));
            int endIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeEnd->text()));
            for (int loop = startIndex; loop < endIndex; loop++) {
                EveProject::getInstance()->getFrameByIndex(loop)->addCommand(command);
            }
        }
    }
};

void EasyVideoEditor::changeBrightnessApplyButtonClicked() {
    if (EveProject::getInstance()->getCurrentFrameNumber() != -1) { // If there is more than one frame.
        QLineEdit* rangeStart = ui.edt_changebrightness_rangestart;
        QLineEdit* rangeEnd = ui.edt_changebrightness_rangeend;
        Command* command = new ChangeBrightness(true,
            ui.edt_changebrightness_brightness->text().toInt()
        );

        if (ui.rbtn_changebrightness_currentframe->isChecked()) {
            EveProject::getInstance()->getCurrentFrame()->addCommand(command);
        }
        else if (ui.rbtn_changebrightness_allframe->isChecked()) {
            std::vector<Frame*>* allFrames = EveProject::getInstance()->getFrameList();
            for (int loop = 0; loop < allFrames->size(); loop++) {
                allFrames->at(loop)->addCommand(command);
            }
        }
        else if (ui.rbtn_changebrightness_rangeframe->isChecked()) {
            int startIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeStart->text()));
            int endIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeEnd->text()));
            for (int loop = startIndex; loop < endIndex; loop++) {
                EveProject::getInstance()->getFrameByIndex(loop)->addCommand(command);
            }
        }
    }
};

void EasyVideoEditor::changeContrastApplyButtonClicked() {
    if (EveProject::getInstance()->getCurrentFrameNumber() != -1) { // If there is more than one frame.
        QLineEdit* rangeStart = ui.edt_changecontrast_rangestart;
        QLineEdit* rangeEnd = ui.edt_changecontrast_rangeend;
        Command* command = new ChangeContrast(true,
            ui.edt_changecontrast_contrast->text().toInt()
        );

        if (ui.rbtn_changecontrast_currentframe->isChecked()) {
            EveProject::getInstance()->getCurrentFrame()->addCommand(command);
        }
        else if (ui.rbtn_changecontrast_allframe->isChecked()) {
            std::vector<Frame*>* allFrames = EveProject::getInstance()->getFrameList();
            for (int loop = 0; loop < allFrames->size(); loop++) {
                allFrames->at(loop)->addCommand(command);
            }
        }
        else if (ui.rbtn_changecontrast_rangeframe->isChecked()) {
            int startIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeStart->text()));
            int endIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeEnd->text()));
            for (int loop = startIndex; loop < endIndex; loop++) {
                EveProject::getInstance()->getFrameByIndex(loop)->addCommand(command);
            }
        }
    }
};

void EasyVideoEditor::filterApplyButtonClicked() {};

void EasyVideoEditor::chromakeyApplyButtonClicked() {};

void EasyVideoEditor::transitionApplyButtonClicked() {};

void EasyVideoEditor::addImageApplyButtonClicked() {
    QString addImagePath = ui.label_addimage_path->text();

    if (!addImagePath.isEmpty()) {
        Image* image = new Image(addImagePath.toStdString());
        EveProject::getInstance()->addImage(image);

        QLineEdit* rangeStart = ui.edt_addimage_rangestart;
        QLineEdit* rangeEnd = ui.edt_addimage_rangeend;

        Command* command = new AddImage(
            true,
            image,
            ui.edt_addimage_x->text().toInt(),
            ui.edt_addimage_y->text().toInt(),
            ui.edt_addimage_width->text().toInt(),
            ui.edt_addimage_height->text().toInt()
        );

        if (ui.rbtn_addimage_currentframe->isChecked()) {
            EveProject::getInstance()->getCurrentFrame()->addCommand(command);
        }
        else if (ui.rbtn_addimage_allframe->isChecked()) {
            std::vector<Frame*>* allFrames = EveProject::getInstance()->getFrameList();
            for (int loop = 0; loop < allFrames->size(); loop++) {
                allFrames->at(loop)->addCommand(command);
            }
        }
        else if (ui.rbtn_addimage_rangeframe->isChecked()) {
            int startIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeStart->text()));
            int endIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeEnd->text()));
            for (int loop = startIndex; loop < endIndex; loop++) {
                EveProject::getInstance()->getFrameByIndex(loop)->addCommand(command);
            }
        }
    }
};

void EasyVideoEditor::addVideoApplyButtonClicked() {};

void EasyVideoEditor::cutVideoApplyButtonClicked() {};

void EasyVideoEditor::resizeApplyButtonClicked() {};

void EasyVideoEditor::changePlaySpeedButtonClicked() {};

void EasyVideoEditor::addSubtitleButtonClicked() {
    
    if (ui.edt_addsubtitle_subtitle->toPlainText() != "") {
        int option = 0;
        int rangeStart = ui.edt_addsubtitle_rangestart->text().toInt();
        int rangeEnd = ui.edt_addsubtitle_rangeend->text().toInt();

        if (ui.radioBtn_addsubtitle_top->isChecked())
            option = 1; 
        else if (ui.radioBtn_addsubtitle_middle->isChecked())
            option = 2;
        else if (ui.radioBtn_addsubtitle_low->isChecked())
            option = 3; 

        Command* command = new AddSubtitle(
            true,
            ui.edt_addsubtitle_subtitle->toPlainText().toStdString(),
            ui.cmbox_addsubtitle_font->currentIndex(),
            option,
            ui.spbox_addsubtitle_font_size->value(),
            ui.edt_addsubtitle_color_red->text().toInt(),
            ui.edt_addsubtitle_color_green->text().toInt(),
            ui.edt_addsubtitle_color_blue->text().toInt()
        );
    }
    
};

void EasyVideoEditor::addImageSelectButtonClicked() {
    QString addImagePath = QFileDialog::getOpenFileName(this, "Select image files to edit", QDir::homePath(), tr("Video Files (*.png *.jpg *.bmp)"));
    ui.label_addimage_path->setText(addImagePath);
};
    
void EasyVideoEditor::addVideoSelectButtonClicked() {
    QString addVideoPath = QFileDialog::getOpenFileName(this, "Select video files to edit", QDir::homePath(), tr("Video Files (*.mp4 *.avi *.wmv *.mov)"));
    ui.label_addvideo_path->setText(addVideoPath);
};
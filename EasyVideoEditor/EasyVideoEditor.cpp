#include "EasyVideoEditor.h"

int EasyVideoEditor::top = 0;
int EasyVideoEditor::down = 0;
int EasyVideoEditor::left = 0;
int EasyVideoEditor::right = 0;
EasyVideoEditor::Mode EasyVideoEditor::mode = EasyVideoEditor::Mode::MODE_EDIT;
QMutex EasyVideoEditor::mutex;
cv::Size EasyVideoEditor::resizeData;
QMetaObject::Connection EasyVideoEditor::encodingVideoThreadConnection;

EasyVideoEditor::EasyVideoEditor(QWidget* parent) : QMainWindow(parent){
    ui.setupUi(this);
    Widgets::getInstance()->initWidgets(this);

    ////// Init ui.
    ui.w_encodingpage->setVisible(false);
    ui.btn_pause->setVisible(false);
    ui.w_contentarea->setEnabled(false);
    ui.w_videocontrolarea->setEnabled(false);
    ui.edt_coloremphasis_red->setValidator(new QIntValidator(-255, 255, this));
    ui.edt_coloremphasis_green->setValidator(new QIntValidator(-255, 255, this));
    ui.edt_coloremphasis_blue->setValidator(new QIntValidator(-255, 255, this));
    ui.edt_changebrightness_brightness->setValidator(new QIntValidator(0, 100, this));
    ui.edt_changecontrast_contrast->setValidator(new QIntValidator(0, 100, this));
    ui.edt_filter_clarity->setValidator(new QIntValidator(0, 100, this));
    ui.edt_chromakey_huestart->setValidator(new QIntValidator(0, 180, this));
    ui.edt_chromakey_hueend->setValidator(new QIntValidator(0, 180, this));
    ui.edt_chromakey_valstart->setValidator(new QIntValidator(0, 255, this));
    ui.edt_chromakey_valend->setValidator(new QIntValidator(0, 255, this));
    ui.edt_chromakey_satstart->setValidator(new QIntValidator(0, 255, this));
    ui.edt_chromakey_satend->setValidator(new QIntValidator(0, 255, this));
    ui.edt_transition_fadein_range->setValidator(new QIntValidator(0, 36000, this));
    ui.edt_transition_fadeout_range->setValidator(new QIntValidator(0, 36000, this));
    ui.edt_cutvideo_framerange->setValidator(new QIntValidator(0, 36000, this));
    ui.edt_changeplayspeed_speed->setValidator(new QDoubleValidator(0.f, 100.f, 10, this));
    ui.edt_addsubtitle_color_red->setValidator(new QIntValidator(0, 255, this));
    ui.edt_addsubtitle_color_blue->setValidator(new QIntValidator(0, 255, this));
    ui.edt_addsubtitle_color_green->setValidator(new QIntValidator(0, 255, this));
    ui.sd_coloremphasis_red->setStyleSheet("QSlider::handle:horizontal {background: red;} ");
    ui.sd_coloremphasis_green->setStyleSheet("QSlider::handle:horizontal {background: green;} ");
    ui.sd_coloremphasis_blue->setStyleSheet("QSlider::handle:horizontal {background: blue;} ");
    ui.sd_changebrightness_brightness->setStyleSheet("QSlider::handle:horizontal {background: yellow;} ");
    QStringList fontList = QFontDatabase::families();
    for(QString fontName : fontList) {
        ui.cmbox_addsubtitle_font->addItem(fontName);
    }
    std::vector<QGraphicsDropShadowEffect*> buttonEffects;
    for (int loop = 0; loop <37; loop++) {
        QGraphicsDropShadowEffect* videoControlEffect = new QGraphicsDropShadowEffect();
        videoControlEffect->setBlurRadius(6);
        videoControlEffect->setOffset(2, 2);
        buttonEffects.push_back(videoControlEffect);
    }
    ui.btn_play->setGraphicsEffect(buttonEffects.at(0));
    ui.btn_pause->setGraphicsEffect(buttonEffects.at(1));
    ui.btn_reset->setGraphicsEffect(buttonEffects.at(2));
    ui.btn_forward5seconds->setGraphicsEffect(buttonEffects.at(3));
    ui.btn_backward5seconds->setGraphicsEffect(buttonEffects.at(4));
    ui.btn_chromakey_filepicker->setGraphicsEffect(buttonEffects.at(5));
    ui.btn_addimage_apply->setGraphicsEffect(buttonEffects.at(6));
    ui.btn_addsubtitle_apply->setGraphicsEffect(buttonEffects.at(7));
    ui.btn_addvideo_apply->setGraphicsEffect(buttonEffects.at(8));
    ui.btn_changebrightness_apply->setGraphicsEffect(buttonEffects.at(9));
    ui.btn_changecontrast_apply->setGraphicsEffect(buttonEffects.at(10));
    ui.btn_changeplayspeed_apply->setGraphicsEffect(buttonEffects.at(11));
    ui.btn_chromakey_apply->setGraphicsEffect(buttonEffects.at(12));
    ui.btn_coloremphasis_apply->setGraphicsEffect(buttonEffects.at(13));
    ui.btn_cutvideo_apply->setGraphicsEffect(buttonEffects.at(14));
    ui.btn_filter_apply->setGraphicsEffect(buttonEffects.at(15));
    ui.btn_transition_apply->setGraphicsEffect(buttonEffects.at(16));
    ui.btn_filter_rangestarttocurrent->setGraphicsEffect(buttonEffects.at(17));
    ui.btn_cutvideo_rangestarttocurrent->setGraphicsEffect(buttonEffects.at(18));
    ui.btn_coloremphasis_rangestarttocurrent->setGraphicsEffect(buttonEffects.at(19));
    ui.btn_chromakey_rangestarttocurrent->setGraphicsEffect(buttonEffects.at(20));
    ui.btn_changeplayspeed_rangestarttocurrent->setGraphicsEffect(buttonEffects.at(21));
    ui.btn_changebrightness_rangestarttocurrent->setGraphicsEffect(buttonEffects.at(22));
    ui.btn_addsubtitle_rangestarttocurrent->setGraphicsEffect(buttonEffects.at(23));
    ui.btn_addimage_rangestarttocurrent->setGraphicsEffect(buttonEffects.at(24));
    ui.btn_filter_rangeendtocurrent->setGraphicsEffect(buttonEffects.at(25));
    ui.btn_cutvideo_rangeendtocurrent->setGraphicsEffect(buttonEffects.at(26));
    ui.btn_coloremphasis_rangeendtocurrent->setGraphicsEffect(buttonEffects.at(27));
    ui.btn_chromakey_rangeendtocurrent->setGraphicsEffect(buttonEffects.at(28));
    ui.btn_changeplayspeed_rangeendtocurrent->setGraphicsEffect(buttonEffects.at(29));
    ui.btn_changebrightness_rangeendtocurrent->setGraphicsEffect(buttonEffects.at(30));
    ui.btn_addsubtitle_rangeendtocurrent->setGraphicsEffect(buttonEffects.at(31));
    ui.btn_addimage_rangeendtocurrent->setGraphicsEffect(buttonEffects.at(32));
    ui.btn_addimage_select_path->setGraphicsEffect(buttonEffects.at(33));
    ui.btn_addvideo_select_path->setGraphicsEffect(buttonEffects.at(34));
    ui.btn_changecontrast_rangestarttocurrent->setGraphicsEffect(buttonEffects.at(35));
    ui.btn_changecontrast_rangeendtocurrent->setGraphicsEffect(buttonEffects.at(36));
    ui.menu_encoding->setEnabled(false);
   

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
    new SideMenu(ui.btn_changeplayspeed, ui.w_changeplayspeed);
    new SideMenu(ui.btn_addsubtitle, ui.w_addsubtitle);
    SideMenu::selectSideMenu(ui.btn_coloremphasis);
    addImageXValidator = new QIntValidator(0, 0, this);
    addImageYValidator = new QIntValidator(0, 0, this);
    addImageWidthValidator = new QIntValidator(0, 0, this);
    addImageHeightValidator = new QIntValidator(0, 0, this);
    ui.edt_addimage_x->setValidator(addImageXValidator);
    ui.edt_addimage_y->setValidator(addImageYValidator);
    ui.edt_addimage_width->setValidator(addImageWidthValidator);
    ui.edt_addimage_height->setValidator(addImageHeightValidator);
    ui.sd_videoprogress->installEventFilter(new VideoProgressEventFilter(ui.lbl_videoframe, ui.sd_videoprogress, ui.lbl_currentplaytime, this));
    
    ////// Init signal, slot.
    connect(ui.menu_newproject, SIGNAL(triggered()), this, SLOT(newProjectMenuClicked()));
    connect(ui.menu_encodingto_avi, SIGNAL(triggered()), this, SLOT(encodingToAviMenuClicked()));
    connect(ui.menu_encodingto_mp4, SIGNAL(triggered()), this, SLOT(encodingToMp4MenuClicked()));
    connect(ui.menu_encodingto_wmv, SIGNAL(triggered()), this, SLOT(encodingToWmvMenuClicked()));
    connect(ui.menu_encodingto_mov, SIGNAL(triggered()), this, SLOT(encodingToMovMenuClicked()));
    connect(ui.menu_exit, SIGNAL(triggered()), this, SLOT(exitMenuClicked()));
    connect(ui.btn_coloremphasis, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_changebrightness, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_changecontrast, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_filter, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_chromakey, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_transition, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_addimage, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_addvideo, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_cutvideo, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_changeplayspeed, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.btn_addsubtitle, SIGNAL(clicked()), this, SLOT(sideMenuClicked()));
    connect(ui.sd_videoprogress, SIGNAL(sliderMoved(int)), this, SLOT(videoProgressSliderMoved(int)));
    connect(ui.btn_play, SIGNAL(clicked()), this, SLOT(playButtonClicked()));
    connect(ui.btn_pause, SIGNAL(clicked()), this, SLOT(pauseButtonClicked()));
    connect(ui.btn_reset, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));
    connect(ui.btn_forward5seconds, SIGNAL(clicked()), this, SLOT(forward5SecondsButtonclicked()));
    connect(ui.btn_backward5seconds, SIGNAL(clicked()), this, SLOT(backward5SecondsButtonClicked()));
    connect(ui.btn_addimage_select_path, SIGNAL(clicked()), this, SLOT(addImageSelectButtonClicked()));
    connect(ui.rbtn_addimage_currentframe, SIGNAL(clicked()), this, SLOT(addImageCurrentFrameButtonClicked()));
    connect(ui.rbtn_addimage_allframe, SIGNAL(clicked()), this, SLOT(addImageAllFrameButtonClicked()));
    connect(ui.rbtn_addimage_rangeframe, SIGNAL(clicked()), this, SLOT(addImageRangeFrameButtonClicked()));
    connect(ui.btn_addvideo_select_path, SIGNAL(clicked()), this, SLOT(addVideoSelectButtonClicked()));
    connect(ui.rbtn_addsubtitle_currentframe, SIGNAL(clicked()), this, SLOT(addSubtitleCurrentFrameButtonClicked()));
    connect(ui.rbtn_addsubtitle_allframe, SIGNAL(clicked()), this, SLOT(addSubtitleAllFrameButtonClicked()));
    connect(ui.rbtn_addsubtitle_rangeframe, SIGNAL(clicked()), this, SLOT(addSubtitleRangeFrameButtonClicked()));
    connect(ui.btn_chromakey_filepicker, SIGNAL(clicked()), this, SLOT(chromakeyFilePickerButtonClicked()));
    connect(ui.btn_coloremphasis_rangestarttocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_coloremphasis_rangeendtocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_changebrightness_rangestarttocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_changebrightness_rangeendtocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_changecontrast_rangestarttocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_changecontrast_rangeendtocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_filter_rangestarttocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_filter_rangeendtocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_chromakey_rangestarttocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_chromakey_rangeendtocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_addimage_rangestarttocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_addimage_rangeendtocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_cutvideo_rangestarttocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_cutvideo_rangeendtocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_changeplayspeed_rangestarttocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_changeplayspeed_rangeendtocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_addsubtitle_rangestarttocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.btn_addsubtitle_rangeendtocurrent, SIGNAL(clicked()), this, SLOT(getCurrentFrameTime()));
    connect(ui.edt_addimage_x, SIGNAL(textChanged(QString)), this, SLOT(addImageXUpdated(QString)));
    connect(ui.edt_addimage_y, SIGNAL(textChanged(QString)), this, SLOT(addImageYUpdated(QString)));
    connect(ui.edt_addimage_width, SIGNAL(textChanged(QString)), this, SLOT(addImageWidthUpdated(QString)));
    connect(ui.edt_addimage_height, SIGNAL(textChanged(QString)), this, SLOT(addImageHeightUpdated(QString)));

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

    // Connect update smaple frame.
    connect(ui.rbtn_filter_colorsense_none, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.rbtn_filter_colorsense_gray, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.rbtn_filter_colorsense_warm, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.rbtn_filter_colorsense_cool, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.rbtn_filter_colorsense_bright, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.rbtn_chromakey_custom, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.rbtn_chromakey_white, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.rbtn_chromakey_black, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.rbtn_chromakey_green, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.rbtn_chromakey_blue, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.cb_chromakey_reverse, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.edt_chromakey_huestart, SIGNAL(textChanged(QString)), this, SLOT(updateSampleFrame()));
    connect(ui.edt_chromakey_hueend, SIGNAL(textChanged(QString)), this, SLOT(updateSampleFrame()));
    connect(ui.edt_chromakey_valstart, SIGNAL(textChanged(QString)), this, SLOT(updateSampleFrame()));
    connect(ui.edt_chromakey_valend, SIGNAL(textChanged(QString)), this, SLOT(updateSampleFrame()));
    connect(ui.edt_chromakey_satstart, SIGNAL(textChanged(QString)), this, SLOT(updateSampleFrame()));
    connect(ui.edt_chromakey_satend, SIGNAL(textChanged(QString)), this, SLOT(updateSampleFrame()));
    connect(ui.edt_addsubtitle_subtitle, SIGNAL(textChanged()), this, SLOT(updateSampleFrame()));
    connect(ui.radioBtn_addsubtitle_top, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.radioBtn_addsubtitle_middle, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.radioBtn_addsubtitle_low, SIGNAL(clicked()), this, SLOT(updateSampleFrame()));
    connect(ui.spbox_addsubtitle_font_size, SIGNAL(textChanged(QString)), this, SLOT(updateSampleFrame()));
    connect(ui.cmbox_addsubtitle_font, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSampleFrame()));
    connect(ui.edt_addsubtitle_color_red, SIGNAL(textChanged(QString)), this, SLOT(updateSampleFrame()));
    connect(ui.edt_addsubtitle_color_green, SIGNAL(textChanged(QString)), this, SLOT(updateSampleFrame()));
    connect(ui.edt_addsubtitle_color_blue, SIGNAL(textChanged(QString)), this, SLOT(updateSampleFrame()));
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
        editingFrame.getCommandAppliedFrameData(-1, -1, &showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
    }
    else if (SideMenu::selectedSideMenu() == Command::CommandType::CHANGE_BRIGHTNESS) {
        (*EveProject::getInstance()->getCurrentFrame()).copyTo(&editingFrame);
        ChangeBrightness changeBrightness(false,
            ui.edt_changebrightness_brightness->text().toInt()
        );
        editingFrame.addCommand(&changeBrightness);
        cv::Mat showFrame;
        editingFrame.getCommandAppliedFrameData(-1, -1, &showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
    }
    else if (SideMenu::selectedSideMenu() == Command::CommandType::CHANGE_CONTRAST) {
        (*EveProject::getInstance()->getCurrentFrame()).copyTo(&editingFrame);
        ChangeContrast changeContrast(false,
            ui.edt_changecontrast_contrast->text().toInt()
        );
        editingFrame.addCommand(&changeContrast);
        cv::Mat showFrame;
        editingFrame.getCommandAppliedFrameData(-1, -1, &showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
    }
    else if (SideMenu::selectedSideMenu() == Command::CommandType::FILTER) {
        (*EveProject::getInstance()->getCurrentFrame()).copyTo(&editingFrame);
        Filter::FilterType filterType;
        if (ui.rbtn_filter_colorsense_none->isChecked()) filterType = Filter::FilterType::NONE;
        else if (ui.rbtn_filter_colorsense_gray->isChecked()) filterType = Filter::FilterType::GRAY;
        else if (ui.rbtn_filter_colorsense_warm->isChecked()) filterType = Filter::FilterType::WARM;
        else if (ui.rbtn_filter_colorsense_cool->isChecked()) filterType = Filter::FilterType::COOL;
        else if (ui.rbtn_filter_colorsense_bright->isChecked()) filterType = Filter::FilterType::BRIGHT;

        Filter filter(false,
            ui.edt_filter_clarity->text().toInt(),
            filterType
        );

        editingFrame.addCommand(&filter);
        cv::Mat showFrame;
        editingFrame.getCommandAppliedFrameData(-1, -1, &showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
    }
    else if (SideMenu::selectedSideMenu() == Command::CommandType::CHROMAKEY) {
        if (!ui.lbl_chromakey_backgroundfilepath->text().isEmpty()) {
            (*EveProject::getInstance()->getCurrentFrame()).copyTo(&editingFrame);

            Image image(ui.lbl_chromakey_backgroundfilepath->text().toStdString());
            image.loadResource();

            Chromakey* chromakey;
            if (ui.rbtn_chromakey_custom->isChecked()) {
                chromakey = new Chromakey(false
                    , ui.edt_chromakey_huestart->text().toInt(), ui.edt_chromakey_hueend->text().toInt()
                    , ui.edt_chromakey_satstart->text().toInt(), ui.edt_chromakey_satend->text().toInt()
                    , ui.edt_chromakey_valstart->text().toInt(), ui.edt_chromakey_valend->text().toInt()
                    , !ui.cb_chromakey_reverse->isChecked(), -1);
            }
            else if (ui.rbtn_chromakey_white->isChecked()) {
                chromakey = new Chromakey(false
                    , 0, 180, 0, 255, 200, 255
                    , !ui.cb_chromakey_reverse->isChecked(), -1);
            }
            else if (ui.rbtn_chromakey_black->isChecked()) {
                chromakey = new Chromakey(false
                    , 0, 180, 0, 255, 0, 30
                    , !ui.cb_chromakey_reverse->isChecked(), -1);
            }
            else if (ui.rbtn_chromakey_green->isChecked()) {
                chromakey = new Chromakey(false
                    , 50, 80, 150, 255, 0, 255
                    , !ui.cb_chromakey_reverse->isChecked(), -1);
            }
            else if (ui.rbtn_chromakey_blue->isChecked()) {
                chromakey = new Chromakey(false
                    , 100, 140, 150, 255, 0, 255
                    , !ui.cb_chromakey_reverse->isChecked(), -1);
            }

            cv::Mat showFrame;
            editingFrame.getCommandAppliedFrameData(-1, -1, &showFrame, true);
            (*chromakey)(&showFrame, &image);
            UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);

            free(chromakey);
        } else {
            cv::Mat showFrame;
            Frame* frame = EveProject::getInstance()->getCurrentFrame();
            frame->getCommandAppliedFrameData(-1, -1, &showFrame, true);
            UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
        }
    }
    else if (SideMenu::selectedSideMenu() == Command::CommandType::ADD_IMAGE) {
        if (!ui.label_addimage_path->text().isEmpty() && ui.edt_addimage_width->text().toInt() != 0 && ui.edt_addimage_height->text().toInt() != 0) {
            (*EveProject::getInstance()->getCurrentFrame()).copyTo(&editingFrame);

            Image image(ui.label_addimage_path->text().toStdString());
            image.loadResource();

            AddImage addImage(
                false,
                &image,
                ui.edt_addimage_x->text().toInt(),
                ui.edt_addimage_y->text().toInt(),
                ui.edt_addimage_width->text().toInt(),
                ui.edt_addimage_height->text().toInt()
            );

            cv::Mat showFrame;
            editingFrame.getCommandAppliedFrameData(-1, -1, &showFrame, true);
            addImage(&showFrame, &image);
            UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
        }
        else {
            cv::Mat showFrame;
            Frame* frame = EveProject::getInstance()->getCurrentFrame();
            frame->getCommandAppliedFrameData(-1, -1, &showFrame, true);
            UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
        }
    }
    else if (SideMenu::selectedSideMenu() == Command::CommandType::ADD_SUBTITLE) {
            (*EveProject::getInstance()->getCurrentFrame()).copyTo(&editingFrame);
        int option = 0;

        if (ui.radioBtn_addsubtitle_top->isChecked())
            option = 1;
        else if (ui.radioBtn_addsubtitle_middle->isChecked())
            option = 2;
        else if (ui.radioBtn_addsubtitle_low->isChecked())
            option = 3;

        AddSubtitle addSubtitle(
            false,
            ui.edt_addsubtitle_subtitle->toPlainText(),
            ui.cmbox_addsubtitle_font->itemText(ui.cmbox_addsubtitle_font->currentIndex()),
            option,
            ui.spbox_addsubtitle_font_size->value(),
            ui.edt_addsubtitle_color_red->text().toInt(),
            ui.edt_addsubtitle_color_green->text().toInt(),
            ui.edt_addsubtitle_color_blue->text().toInt()
        );

        editingFrame.addCommand(&addSubtitle);
        cv::Mat showFrame;
        editingFrame.getCommandAppliedFrameData(-1, -1, &showFrame, true);
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
    QPixmap pixmap(ui.lbl_videoframe->size());
    pixmap.fill(QColor(0, 0, 0));
    ui.lbl_videoframe->setPixmap(pixmap);

    EveProject::getInstance()->clear(this);

    mutex.unlock();
}

void EasyVideoEditor::newProject() {
    QString baseVideoPath = QFileDialog::getOpenFileName(this, QString("편집할 동영상 파일 선택"), QDir::homePath(), QString("동영상 (*.mp4 *.avi *.wmv *.mov)"));
    if (!baseVideoPath.isEmpty()) {
        clear();
        ui.menu_encoding->setEnabled(true);
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

        EveProject::getInstance()->setCurrentFrameNumber(0);
        ui.lbl_maxplaytime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(EveProject::getInstance()->getFrameList()->size() - 1)));
        ui.lbl_currentplaytime->setText("00:00:00.000");
        ui.sd_videoprogress->setMinimum(0);
        ui.sd_videoprogress->setMaximum(EveProject::getInstance()->getFrameList()->size() - 1);
        ui.sd_videoprogress->setPageStep(EveProject::getInstance()->getFrameList()->size() / 10);
        ui.sd_videoprogress->setValue(0);

        addImageXValidator->setRange(0, EveProject::getInstance()->getBaseWidth());
        addImageYValidator->setRange(0, EveProject::getInstance()->getBaseHeight());
        addImageWidthValidator->setRange(0, EveProject::getInstance()->getBaseWidth());
        addImageHeightValidator->setRange(0, EveProject::getInstance()->getBaseHeight());

        cv::Mat showFrame;
        EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(-1, -1, &showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);

        updateInformationArea();

    }
}

void EasyVideoEditor::encodingVideo(QString encodingType) {
    mutex.lock();
    if (mode == Mode::MODE_WATCH_PLAY) {
        mode = Mode::MODE_WATCH_PAUSE;
    }
    mutex.unlock();
    
    QString saveFilePath = QFileDialog::getSaveFileName(this, QString("편집한 동영상 저장"), QDir::homePath(), QString("*.").append(encodingType));
    
    if (!saveFilePath.isEmpty()) {
        QObject::disconnect(encodingVideoThreadConnection);
        if (encodingVideoThread == NULL) {
            encodingVideoThread = new EncodingVideo(this, encodingType, saveFilePath);
        }
        else {
            encodingVideoThread->setData(encodingType, saveFilePath);
        }
        encodingVideoThreadConnection = connect(encodingVideoThread, SIGNAL(updateProgress(int)), this, SLOT(updateEncodingProgressBar(int)));
        encodingVideoThread->start();
    }
}

void EasyVideoEditor::updateInformationArea() {
    int size = EveProject::getInstance()->getFrameList()->size();
    int width = EveProject::getInstance()->getBaseWidth();
    int height = EveProject::getInstance()->getBaseHeight();
    int delay = EveProject::getInstance()->getBaseDelay();
    double fps = EveProject::getInstance()->getBaseFps();

    ui.tbr_allframe->setText(QString::number(size)+" ms");
    ui.tbr_width->setText(QString::number(width)+" px");
;   ui.tbr_height->setText(QString::number(height)+" px");
    ui.tbr_delay->setText(QString::number(delay)+" ms");
    ui.tbr_fps->setText(QString::number(fps)+" /sec");
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
    if ((e->key() == Qt::Key_E) && QApplication::keyboardModifiers() && Qt::ControlModifier && EveProject::getInstance()->getFrameList()->size() > 0) {
        mutex.lock();
        if (mode == Mode::MODE_EDIT) {
            mode = Mode::MODE_WATCH_PAUSE;
            ui.w_sidemenuarea->setEnabled(false);
            ui.w_sidemenupagearea->setEnabled(false);
            ui.w_videocontrolarea->setEnabled(true);

            cv::Mat showFrame;
            Frame* frame = EveProject::getInstance()->getCurrentFrame();
            frame->getCommandAppliedFrameData(-1, -1, &showFrame, true);
            UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
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
            updateSampleFrame();
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
    encodingVideo("mp4");
}

void EasyVideoEditor::encodingToAviMenuClicked(){
    encodingVideo("avi");
}

void EasyVideoEditor::encodingToWmvMenuClicked(){
    encodingVideo("wmv");
}

void EasyVideoEditor::encodingToMovMenuClicked(){
    encodingVideo("mov");
}

void EasyVideoEditor::exitMenuClicked(){
    QApplication::exit();
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
    updateSampleFrame();
}

void EasyVideoEditor::videoProgressSliderMoved(int value) {
    mutex.lock();
    EveProject::getInstance()->setCurrentFrameNumber(value);
    if (mode == Mode::MODE_WATCH_PAUSE) {
        ui.lbl_currentplaytime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(value)));
        cv::Mat showFrame;
        EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(-1, -1, &showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
    }
    mutex.unlock();
}

void EasyVideoEditor::playButtonClicked() {
    mutex.lock();
    if (EveProject::getInstance()->getCurrentFrameNumber() == EveProject::getInstance()->getFrameList()->size() - 1)
        EveProject::getInstance()->setCurrentFrameNumber(0);
    mode = Mode::MODE_WATCH_PLAY;
    ui.btn_play->setVisible(false);
    ui.btn_pause->setVisible(true);
    mutex.unlock();
    if (playVideoThread == NULL) {
        playVideoThread = new PlayVideo(this);
    }
    playVideoThread->start();
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
    EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(-1, -1, &showFrame, true);
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
        EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(-1, -1, &showFrame, true);
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
        EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(-1, -1, &showFrame, true);
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

void EasyVideoEditor::filterApplyButtonClicked() {
    if (EveProject::getInstance()->getCurrentFrameNumber() != -1) { // If there is more than one frame.
        QLineEdit* rangeStart = ui.edt_filter_rangestart;
        QLineEdit* rangeEnd = ui.edt_filter_rangeend;

        Filter::FilterType filterType;
        if (ui.rbtn_filter_colorsense_none->isChecked()) filterType = Filter::FilterType::NONE;
        else if (ui.rbtn_filter_colorsense_gray->isChecked()) filterType = Filter::FilterType::GRAY;
        else if (ui.rbtn_filter_colorsense_warm->isChecked()) filterType = Filter::FilterType::WARM;
        else if (ui.rbtn_filter_colorsense_cool->isChecked()) filterType = Filter::FilterType::COOL;
        else if (ui.rbtn_filter_colorsense_bright->isChecked()) filterType = Filter::FilterType::BRIGHT;

        Command* command = new Filter(true,
            ui.edt_filter_clarity->text().toInt(), filterType
        );

        if (ui.rbtn_filter_currentframe->isChecked()) {
            EveProject::getInstance()->getCurrentFrame()->addCommand(command);
        }
        else if (ui.rbtn_filter_allframe->isChecked()) {
            std::vector<Frame*>* allFrames = EveProject::getInstance()->getFrameList();
            for (int loop = 0; loop < allFrames->size(); loop++) {
                allFrames->at(loop)->addCommand(command);
            }
        }
        else if (ui.rbtn_filter_rangeframe->isChecked()) {
            int startIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeStart->text()));
            int endIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeEnd->text()));
            for (int loop = startIndex; loop < endIndex; loop++) {
                EveProject::getInstance()->getFrameByIndex(loop)->addCommand(command);
            }
        }
    }
};

void EasyVideoEditor::chromakeyApplyButtonClicked() {
    QString backgroundImagePath = ui.lbl_chromakey_backgroundfilepath->text();

    if (!backgroundImagePath.isEmpty()) {
        Image* image = new Image(backgroundImagePath.toStdString());
        EveProject::getInstance()->addImage(image);
        QLineEdit* rangeStart = ui.edt_chromakey_rangestart;
        QLineEdit* rangeEnd = ui.edt_chromakey_rangeend;

        Command* command;
        if (ui.rbtn_chromakey_custom->isChecked()) {
            command = new Chromakey(true
                , ui.edt_chromakey_huestart->text().toInt(), ui.edt_chromakey_hueend->text().toInt()
                , ui.edt_chromakey_satstart->text().toInt(), ui.edt_chromakey_satend->text().toInt()
                , ui.edt_chromakey_valstart->text().toInt(), ui.edt_chromakey_valend->text().toInt()
                , !ui.cb_chromakey_reverse->isChecked(), image->getResourceId());
        } else if (ui.rbtn_chromakey_white->isChecked()) {
            command = new Chromakey(true
                , 0, 180, 0, 255, 200, 255
                , !ui.cb_chromakey_reverse->isChecked(), image->getResourceId());
        } else if (ui.rbtn_chromakey_black->isChecked()) {
            command = new Chromakey(true
                , 0, 180, 0, 255, 0, 30
                , !ui.cb_chromakey_reverse->isChecked(), image->getResourceId());
        } else if (ui.rbtn_chromakey_green->isChecked()) {
            command = new Chromakey(true
                , 50, 80, 150, 255, 0, 255
                , !ui.cb_chromakey_reverse->isChecked(), image->getResourceId());
        } else if (ui.rbtn_chromakey_blue->isChecked()) {
            command = new Chromakey(true
                , 100, 140, 150, 255, 0, 255
                , !ui.cb_chromakey_reverse->isChecked(), image->getResourceId());
        }

        if (ui.rbtn_chromakey_currentframe->isChecked()) {
            EveProject::getInstance()->getCurrentFrame()->addCommand(command);
        }
        else if (ui.rbtn_chromakey_allframe->isChecked()) {
            std::vector<Frame*>* allFrames = EveProject::getInstance()->getFrameList();
            for (int loop = 0; loop < allFrames->size(); loop++) {
                allFrames->at(loop)->addCommand(command);
            }
        }
        else if (ui.rbtn_chromakey_rangeframe->isChecked()) {
            int startIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeStart->text()));
            int endIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeEnd->text()));
            for (int loop = startIndex; loop < endIndex; loop++) {
                EveProject::getInstance()->getFrameByIndex(loop)->addCommand(command);
            }
        }
    }

};

void EasyVideoEditor::transitionApplyButtonClicked() {
    if (ui.rbtn_transition_fadein->isChecked()) {
        QString transitionTime = ui.edt_transition_fadein_range->text();
        if (!transitionTime.isEmpty()) {
            int startIndex = EveProject::getInstance()->getCurrentFrameNumber();
            double time = transitionTime.toDouble();

            int totalTransitionFrame = EveProject::getInstance()->getBaseFps() * time;
            int endIndex = startIndex + totalTransitionFrame - 1;
            if (endIndex > EveProject::getInstance()->getFrameList()->size() - 1) {
                endIndex = EveProject::getInstance()->getFrameList()->size() - 1;
                totalTransitionFrame = endIndex - startIndex;
            }

            double changeWeight = 1.0f / totalTransitionFrame;

            for (int loop = 0; loop < totalTransitionFrame; loop++) {
                Transition* transition = new Transition(true, changeWeight * loop);
                EveProject::getInstance()->getFrameByIndex(startIndex + loop)->addCommand(transition);
            }

            cv::Mat showFrame;
            EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(-1, -1, &showFrame, true);
            UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
        }
    }
    else if (ui.rbtn_transition_fadeout->isChecked()) {
        QString transitionTime = ui.edt_transition_fadeout_range->text();
        if (!transitionTime.isEmpty()) {
            int startIndex = EveProject::getInstance()->getCurrentFrameNumber();
            double time = transitionTime.toDouble();

            int totalTransitionFrame = EveProject::getInstance()->getBaseFps() * time;
            int endIndex = startIndex + totalTransitionFrame - 1;
            if (endIndex > EveProject::getInstance()->getFrameList()->size() - 1) {
                endIndex = EveProject::getInstance()->getFrameList()->size() - 1;
                totalTransitionFrame = endIndex - startIndex;
            }

            double changeWeight = 1.0f / totalTransitionFrame;

            for (int loop = 0; loop < totalTransitionFrame; loop++) {
                Transition* transition = new Transition(true, 1 - changeWeight * loop);
                EveProject::getInstance()->getFrameByIndex(startIndex + loop)->addCommand(transition);
            }

            cv::Mat showFrame;
            EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(-1, -1, &showFrame, true);
            UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
        }
    }
};

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

void EasyVideoEditor::addVideoApplyButtonClicked() {
    QString addVideoPath = ui.label_addvideo_path->text();
    if(!addVideoPath.isEmpty()){
        Video* addVideo = new Video(0, addVideoPath.toStdString());
        EveProject::getInstance()->addVideo(addVideo);
        std::vector<Frame*> frames;
        for (int loop = 0; loop < addVideo->getFrameCount(); loop++) {
            frames.push_back(new Frame(EveProject::getInstance()->getVideoList()->size() - 1, loop));
        }
        EveProject::getInstance()->addFrames(frames, EveProject::getInstance()->getCurrentFrameNumber());

        ui.lbl_maxplaytime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(EveProject::getInstance()->getFrameList()->size() - 1)));
        ui.sd_videoprogress->setMaximum(EveProject::getInstance()->getFrameList()->size() - 1);
        ui.sd_videoprogress->setPageStep(EveProject::getInstance()->getFrameList()->size() / 10);

        updateInformationArea();
    }
};

void EasyVideoEditor::cutVideoApplyButtonClicked() {
    QLineEdit* rangeStart = ui.edt_cutvideo_rangestart;
    QLineEdit* rangeEnd = ui.edt_cutvideo_rangeend;

    int leftFrame = 0;
    if(ui.rbtn_cutvideo_currentframe->isChecked()){
        Frame* temp =  EveProject::getInstance()->getCurrentFrame();
        int start = EveProject::getInstance()->getFrameIndex(temp);
        leftFrame = EveProject::getInstance()->removeFrame(start);
    }
    else if(ui.rbtn_cutvideo_allframe->isChecked()){
        Frame* temp = EveProject::getInstance()->getCurrentFrame();
        int start = EveProject::getInstance()->getFrameIndex(temp);
        int end = ui.edt_cutvideo_framerange->text().toInt();
        leftFrame = EveProject::getInstance()->removeFrames(start, end);
    }
    else if (ui.rbtn_cutvideo_rangeframe->isChecked()) {
        int startIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeStart->text()));
        int endIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeEnd->text()));
        leftFrame = EveProject::getInstance()->removeFrames(startIndex, (endIndex - startIndex));

    }

    if (leftFrame == 0) {
        clear();
    }
    else {
        EveProject::getInstance()->setCurrentFrameNumber(0);
        ui.lbl_maxplaytime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(EveProject::getInstance()->getFrameList()->size() - 1)));
        ui.lbl_currentplaytime->setText("00:00:00.000");
        ui.sd_videoprogress->setMinimum(0);
        ui.sd_videoprogress->setMaximum(EveProject::getInstance()->getFrameList()->size() - 1);
        ui.sd_videoprogress->setPageStep(EveProject::getInstance()->getFrameList()->size() / 10);
        ui.sd_videoprogress->setValue(0);

        cv::Mat showFrame;
        EveProject::getInstance()->getCurrentFrame()->getCommandAppliedFrameData(-1, -1, &showFrame, true);
        UsefulFunction::showMatToLabel(ui.lbl_videoframe, &showFrame, resizeData, top, down, left, right);
    }


    updateInformationArea();
};

void EasyVideoEditor::changePlaySpeedButtonClicked() {
    QLineEdit* rangeStart = ui.edt_changeplayspeed_rangestart;
    QLineEdit* rangeEnd = ui.edt_changeplayspeed_rangeend;

    double speed = ui.edt_changeplayspeed_speed->text().toDouble();

    if (0 < speed) {
        if (ui.rbtn_changeplayspeed_allframe->isChecked()) {
            EveProject::getInstance()->setBaseFps(EveProject::getInstance()->getBaseFps() * speed);
            EveProject::getInstance()->setBaseDelay(EveProject::getInstance()->getBaseDelay() * (1 / speed));
            EveProject::getInstance()->setCurrentFrameNumber(0);
            ui.lbl_maxplaytime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(EveProject::getInstance()->getFrameList()->size() - 1)));
            ui.lbl_currentplaytime->setText("00:00:00.000");
            ui.sd_videoprogress->setValue(0);
        }
        else if (ui.rbtn_changeplayspeed_rangeframe->isChecked()) {
            int startIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeStart->text()));
            int endIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeEnd->text()));
            if (endIndex > EveProject::getInstance()->getFrameList()->size() - 1) endIndex = EveProject::getInstance()->getFrameList()->size() - 1;

            if (speed < 1) {
                std::vector<Frame*>* allFrames = EveProject::getInstance()->getFrameList();
                int frameGap = 1 / speed;
                for (int loop1 = 0; loop1 < endIndex - startIndex + 1; loop1++) {
                    std::vector<Frame*> addFrames;
                    for (int loop2 = 0; loop2 < frameGap - 1; loop2++) {
                        Frame* frame = new Frame();
                        allFrames->at(startIndex + loop1 * frameGap)->copyTo(frame);
                        addFrames.push_back(frame);
                    }
                    EveProject::getInstance()->addFrames(addFrames, startIndex + frameGap * loop1);
                }
            }
            else {
                int originalSize = EveProject::getInstance()->getFrameList()->size();
                int frameGap = (int)speed;
                int deleteCount = 0;
                for (int loop = 0; loop < originalSize; loop++) {
                    if (loop % frameGap == 0 && loop != 0) {
                        EveProject::getInstance()->removeFrame(loop - deleteCount);
                        deleteCount++;
                    }
                }
            }
            EveProject::getInstance()->setCurrentFrameNumber(0);
            ui.lbl_maxplaytime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(EveProject::getInstance()->getFrameList()->size() - 1)));
            ui.lbl_currentplaytime->setText("00:00:00.000");
            ui.sd_videoprogress->setMinimum(0);
            ui.sd_videoprogress->setMaximum(EveProject::getInstance()->getFrameList()->size() - 1);
            ui.sd_videoprogress->setPageStep(EveProject::getInstance()->getFrameList()->size() / 10);
            ui.sd_videoprogress->setValue(0);
        }
    }

    updateInformationArea();

};

void EasyVideoEditor::addSubtitleButtonClicked() {
    if (ui.edt_addsubtitle_subtitle->toPlainText() != "") {
        int option = 0;
        QLineEdit* rangeStart = ui.edt_addsubtitle_rangestart;
        QLineEdit* rangeEnd = ui.edt_addsubtitle_rangeend;

        if (ui.radioBtn_addsubtitle_top->isChecked())
            option = 1; 
        else if (ui.radioBtn_addsubtitle_middle->isChecked())
            option = 2;
        else if (ui.radioBtn_addsubtitle_low->isChecked())
            option = 3; 

        Command* command = new AddSubtitle(
            true,
            ui.edt_addsubtitle_subtitle->toPlainText(),
            ui.cmbox_addsubtitle_font->itemText(ui.cmbox_addsubtitle_font->currentIndex()),
            option,
            ui.spbox_addsubtitle_font_size->value(),
            ui.edt_addsubtitle_color_red->text().toInt(),
            ui.edt_addsubtitle_color_green->text().toInt(),
            ui.edt_addsubtitle_color_blue->text().toInt()
        );

        if (ui.rbtn_addsubtitle_currentframe->isChecked()) {
            EveProject::getInstance()->getCurrentFrame()->addCommand(command);
        }
        else if (ui.rbtn_addsubtitle_allframe->isChecked()) {
            std::vector<Frame*>* allFrames = EveProject::getInstance()->getFrameList();
            for (int loop = 0; loop < allFrames->size(); loop++) {
                allFrames->at(loop)->addCommand(command);
            }
        }
        else if (ui.rbtn_addsubtitle_rangeframe->isChecked()) {
            int startIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeStart->text()));
            int endIndex = EveProject::getInstance()->getFrameIndex(UsefulFunction::getMillisecondsFromString(rangeEnd->text()));
            for (int loop = startIndex; loop < endIndex; loop++) {
                EveProject::getInstance()->getFrameByIndex(loop)->addCommand(command);
            }
        }
    }
};

void EasyVideoEditor::addSubtitleCurrentFrameButtonClicked() {
    ui.btn_addsubtitle_rangeendtocurrent->setEnabled(false);
    ui.btn_addsubtitle_rangestarttocurrent->setEnabled(false);
    ui.edt_addsubtitle_rangeend->setEnabled(false);
    ui.edt_addsubtitle_rangestart->setEnabled(false);
    ui.label_45->setEnabled(false);
}

void EasyVideoEditor::addSubtitleAllFrameButtonClicked() {
    ui.btn_addsubtitle_rangeendtocurrent->setEnabled(false);
    ui.btn_addsubtitle_rangestarttocurrent->setEnabled(false);
    ui.edt_addsubtitle_rangeend->setEnabled(false);
    ui.edt_addsubtitle_rangestart->setEnabled(false);
    ui.label_45->setEnabled(false);
}

void EasyVideoEditor::addSubtitleRangeFrameButtonClicked() {
    ui.btn_addsubtitle_rangeendtocurrent->setEnabled(true);
    ui.btn_addsubtitle_rangestarttocurrent->setEnabled(true);
    ui.edt_addsubtitle_rangeend->setEnabled(true);
    ui.edt_addsubtitle_rangestart->setEnabled(true);
    ui.label_45->setEnabled(true);
}

void EasyVideoEditor::addImageSelectButtonClicked() {
    QString addImagePath = QFileDialog::getOpenFileName(this, QString("추가할 이미지 선택"), QDir::homePath(), QString("이미지 (*.png *.jpg *.bmp)"));
    ui.label_addimage_path->setText(addImagePath);
    if (!(ui.label_addimage_path->text()).isEmpty()) {
        ui.edt_addimage_height->setEnabled(true);
        ui.edt_addimage_width->setEnabled(true);
        ui.edt_addimage_x->setEnabled(true);
        ui.edt_addimage_y->setEnabled(true);
        ui.label_24->setEnabled(true);
        ui.label_addimage_height->setEnabled(true);
        ui.label_addimage_size_location->setEnabled(true);
        ui.label_addimage_width->setEnabled(true);
        ui.label_addimage_x->setEnabled(true);
        ui.label_addimage_y->setEnabled(true);
        ui.rbtn_addimage_allframe->setEnabled(true);
        ui.rbtn_addimage_currentframe->setEnabled(true);
        ui.rbtn_addimage_rangeframe->setEnabled(true);
        ui.btn_addimage_apply->setEnabled(true);
        updateSampleFrame();
    }
};

void EasyVideoEditor::addImageCurrentFrameButtonClicked() {
    ui.btn_addimage_rangestarttocurrent->setEnabled(false);
    ui.btn_addimage_rangeendtocurrent->setEnabled(false);
    ui.label_27->setEnabled(false);
    ui.edt_addimage_rangeend->setEnabled(false);
    ui.edt_addimage_rangestart->setEnabled(false);
}

void EasyVideoEditor::addImageAllFrameButtonClicked() {
    ui.btn_addimage_rangestarttocurrent->setEnabled(false);
    ui.btn_addimage_rangeendtocurrent->setEnabled(false);
    ui.label_27->setEnabled(false);
    ui.edt_addimage_rangeend->setEnabled(false);
    ui.edt_addimage_rangestart->setEnabled(false);
}

void EasyVideoEditor::addImageRangeFrameButtonClicked() {
    ui.btn_addimage_rangestarttocurrent->setEnabled(true);
    ui.btn_addimage_rangeendtocurrent->setEnabled(true);
    ui.label_27->setEnabled(true);
    ui.edt_addimage_rangeend->setEnabled(true);
    ui.edt_addimage_rangestart->setEnabled(true);
}

void EasyVideoEditor::addVideoSelectButtonClicked() {
    QString addVideoPath = QFileDialog::getOpenFileName(this, QString("추가할 동영상 파일 선택"), QDir::homePath(), QString("동영상 (*.mp4 *.avi *.wmv *.mov)"));
    ui.label_addvideo_path->setText(addVideoPath);

    if (!(ui.label_addvideo_path->text()).isEmpty()) {

    }
};

void EasyVideoEditor::chromakeyFilePickerButtonClicked() {
    QString backgroundImagePath = QFileDialog::getOpenFileName(this, QString("추가할 이미지 선택"), QDir::homePath(), QString("이미지 (*.png *.jpg *.bmp)"));
    if (!backgroundImagePath.isEmpty()) {
        ui.lbl_chromakey_backgroundfilepath->setText(backgroundImagePath);
        updateSampleFrame();
    }
}

void EasyVideoEditor::updateEncodingProgressBar(int value) {
    ui.pb_encoding_progress->setValue(value);
}

void EasyVideoEditor::getCurrentFrameTime() {
    QObject* senderObject = sender();
    if (senderObject == ui.btn_coloremphasis_rangestarttocurrent)
        ui.edt_coloremphasis_rangestart->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_coloremphasis_rangeendtocurrent)
        ui.edt_coloremphasis_rangeend->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_changebrightness_rangestarttocurrent)
        ui.edt_changebrightness_rangestart->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_changebrightness_rangeendtocurrent)
        ui.edt_changebrightness_rangeend->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_changecontrast_rangestarttocurrent)
        ui.edt_changecontrast_rangestart->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_changecontrast_rangeendtocurrent)
        ui.edt_changecontrast_rangeend->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_filter_rangestarttocurrent)
        ui.edt_filter_rangestart->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_filter_rangeendtocurrent)
        ui.edt_filter_rangeend->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_chromakey_rangestarttocurrent)
        ui.edt_chromakey_rangestart->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_chromakey_rangeendtocurrent)
        ui.edt_chromakey_rangeend->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_addimage_rangestarttocurrent)
        ui.edt_addimage_rangestart->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_addimage_rangeendtocurrent)
        ui.edt_addimage_rangeend->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_cutvideo_rangestarttocurrent)
        ui.edt_cutvideo_rangestart->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_cutvideo_rangeendtocurrent)
        ui.edt_cutvideo_rangeend->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_changeplayspeed_rangestarttocurrent)
        ui.edt_changeplayspeed_rangestart->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_changeplayspeed_rangeendtocurrent)
        ui.edt_changeplayspeed_rangeend->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_addsubtitle_rangestarttocurrent)
        ui.edt_addsubtitle_rangestart->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber())));
    else if (senderObject == ui.btn_addsubtitle_rangeendtocurrent)
        ui.edt_addsubtitle_rangeend->setText(
            UsefulFunction::getStringFromMilliseconds(
                EveProject::getInstance()->getFrameTime(
                    EveProject::getInstance()->getCurrentFrameNumber()))); 
}

void EasyVideoEditor::addImageXUpdated(QString value) {
    if (value.isEmpty()) value = "0";
    int x = value.toInt();
    int width = ui.edt_addimage_width->text().toInt();
    if (x + width > EveProject::getInstance()->getBaseWidth()) {
        ui.edt_addimage_width->setText(QString::number(EveProject::getInstance()->getBaseWidth() - x));
    }
    addImageWidthValidator->setRange(0, EveProject::getInstance()->getBaseWidth() - x);
    updateSampleFrame();
}
void EasyVideoEditor::addImageYUpdated(QString value) {
    if (value.isEmpty()) value = "0";
    int y = value.toInt();
    int height = ui.edt_addimage_height->text().toInt();
    if (y + height > EveProject::getInstance()->getBaseHeight()) {
        ui.edt_addimage_height->setText(QString::number(EveProject::getInstance()->getBaseHeight() - y));
    }
    addImageHeightValidator->setRange(0, EveProject::getInstance()->getBaseHeight() - y);
    updateSampleFrame();
}
void EasyVideoEditor::addImageWidthUpdated(QString value) {
    if (value.isEmpty()) value = "0";
    int width = value.toInt();
    int x = ui.edt_addimage_x->text().toInt();
    if (x + width > EveProject::getInstance()->getBaseWidth()) {
        ui.edt_addimage_width->setText(QString::number(EveProject::getInstance()->getBaseWidth() - x));
    }
    updateSampleFrame();
}
void EasyVideoEditor::addImageHeightUpdated(QString value) {
    if (value.isEmpty()) value = "0";
    int height = value.toInt();
    int y = ui.edt_addimage_y->text().toInt();
    if (y + height > EveProject::getInstance()->getBaseHeight()) {
        ui.edt_addimage_height->setText(QString::number(EveProject::getInstance()->getBaseHeight() - y));
    }
    updateSampleFrame();
}
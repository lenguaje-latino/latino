[Code]
//--------Clic-Web
procedure WebImgClic(Sender: TObject);
var
  ErrorCode: Integer;
begin
  ShellExecAsOriginalUser('open', 'https://lenguajelatino.org/', '', '', SW_SHOWNORMAL, ewNoWait, ErrorCode);
end;

//--------Clic-GitHub
procedure GitHubImgClic(Sender: TObject);
var
  ErrorCode: Integer;
begin
  ShellExecAsOriginalUser('open', 'https://github.com/lenguaje-latino/latino', '', '', SW_SHOWNORMAL, ewNoWait, ErrorCode);
end;

//--------Clic-Manual
procedure ManualImgClic(Sender: TObject);
var
  ErrorCode: Integer;
begin
  ShellExecAsOriginalUser('open', 'https://manual.lenguajelatino.org/es/stable/', '', '', SW_SHOWNORMAL, ewNoWait, ErrorCode);
end;

//------------------------------------------------------
<event('InitializeWizard')>
procedure ManualInitializeWizard;
var
  ImageFileName: String;
  WebBtn, GitHubBtn, ManualBtn: TBitmapImage;
  BevelTop: Integer;
begin
//--------Eventos-Web
  ImageFileName         :=    ExpandConstant('{tmp}\web-icon.bmp');
  ExtractTemporaryFile(ExtractFileName(ImageFileName));

  WebBtn                :=    TBitmapImage.Create(WizardForm);
  WebBtn.AutoSize       :=    True;
  WebBtn.Bitmap.LoadFromFile(ImageFileName);
  WebBtn.Hint           :=    CustomMessage('WebHint');
  WebBtn.ShowHint       :=    True;
  WebBtn.Anchors        :=    [akLeft, akBottom];
  BevelTop              :=    WizardForm.Bevel.Top;
  WebBtn.Top            :=    BevelTop + (WizardForm.ClientHeight - BevelTop - WebBtn.Bitmap.height) div 2;
  WebBtn.Left           :=    WebBtn.Top - BevelTop;
  WebBtn.Cursor         :=    crHand;
  WebBtn.OnClick        :=    @WebImgClic;
  WebBtn.Parent         :=    WizardForm;

//--------Eventos-GitHub
  ImageFileName         :=    ExpandConstant('{tmp}\github-icon.bmp');
  ExtractTemporaryFile(ExtractFileName(ImageFileName));

  GitHubBtn             :=    TBitmapImage.Create(WizardForm);
  GitHubBtn.AutoSize    :=    True;
  GitHubBtn.Bitmap.LoadFromFile(ImageFileName);
  GitHubBtn.Hint        :=    CustomMessage('GitHubHint');
  GitHubBtn.ShowHint    :=    True;
  GitHubBtn.Anchors     :=    [akLeft, akBottom];
  BevelTop              :=    WizardForm.Bevel.Top;
  GitHubBtn.Top         :=    BevelTop + (WizardForm.ClientHeight - BevelTop - GitHubBtn.Bitmap.height) div 2;
  GitHubBtn.Left        :=    (GitHubBtn.Top - BevelTop) + (WebBtn.Width + WebBtn.Left);
  GitHubBtn.Cursor      :=    crHand;
  GitHubBtn.OnClick     :=    @GitHubImgClic;
  GitHubBtn.Parent      :=    WizardForm;

//--------Eventos-Manual
  ImageFileName         :=    ExpandConstant('{tmp}\manual-icon.bmp');
  ExtractTemporaryFile(ExtractFileName(ImageFileName));

  ManualBtn             :=    TBitmapImage.Create(WizardForm);
  ManualBtn.AutoSize    :=    True;
  ManualBtn.Bitmap.LoadFromFile(ImageFileName);
  ManualBtn.Hint        :=    CustomMessage('ManualHint');
  ManualBtn.ShowHint    :=    True;
  ManualBtn.Anchors     :=    [akLeft, akBottom];
  BevelTop              :=    WizardForm.Bevel.Top;
  ManualBtn.Top         :=    BevelTop + (WizardForm.ClientHeight - BevelTop - ManualBtn.Bitmap.height) div 2;
  ManualBtn.Left        :=    (ManualBtn.Top - BevelTop) + (GitHubBtn.Width + GitHubBtn.Left);
  ManualBtn.Cursor      :=    crHand;
  ManualBtn.OnClick     :=    @ManualImgClic;
  ManualBtn.Parent      :=    WizardForm;
end;
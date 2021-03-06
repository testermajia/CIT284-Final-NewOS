#include <afxwin.h>
#include <afxdlgs.h>
#include "resource.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include <time.h>

#include "dlgType.h"
#include "DlgMkDir.h"
#include "DlgRename.h"
#include "DlgRmdir.h"
#define IDC_EDIT 500
using namespace std;
//Define filters for use with File Dialog
const wchar_t fileDialogFilter[] =
L"C++ Files (*.cpp) | *.cpp | Header Files(*.h) | *.h | Resource Files(*.rc) | *.rc\
| Text Files(*.txt) | *.txt | All Files(*.*) | *.* || ";
const wchar_t fileDialogExt[] = L"cpp";

//Why global? 
CString findString;
CFindReplaceDialog *findReplaceDialog = NULL;


//Define the application object class

class CApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};



//Define the edit window class
class CWindow : public CFrameWnd
{
private:
	static UINT findMessage;
	CMenu *menu;
	CEdit m_edit;

public:
	CWindow();
	afx_msg void HandleOpen();
	afx_msg void HandlePrint();
	afx_msg void HandleQuit();
	afx_msg void HandleFind();
	afx_msg void HandleDelete();
	afx_msg void HandleUndo();
	afx_msg void HandleDate();
	afx_msg void HandleCut();
	afx_msg void HandleCopy();
	afx_msg void HandlePaste();
	afx_msg void HandleSave();
	afx_msg void HandleClear();
	afx_msg void HandleAbout();
	afx_msg LONG FindHelper(UINT wParam, LONG lParam);
	afx_msg void OnMouseMove(UINT, CPoint);
	DECLARE_MESSAGE_MAP()


	afx_msg void OnDirectoryType();
	afx_msg void OnDirectoryMkdir();
	afx_msg void OnDirectoryChdir();
	afx_msg void OnDirectoryRmdir();
	afx_msg void OnDirectoryAttrib();
	afx_msg void OnDirectoryCopy();
	afx_msg void OnDirectoryRename();
	afx_msg void OnDirectoryCurrent();
	afx_msg void OnDirectoryMove();
	afx_msg void OnDirectoryDirexe();
	afx_msg void OnGameBattleoffice();
	afx_msg void OnGameBrainiac();
	afx_msg void OnGameHenway();

	void setupStartInfo(STARTUPINFO &, PROCESS_INFORMATION &);
};

//The message map

BEGIN_MESSAGE_MAP(CWindow, CFrameWnd)
	ON_COMMAND(IDM_FILE_OPEN, HandleOpen)
	ON_COMMAND(IDM_FILE_PRINT, HandlePrint)
	ON_COMMAND(IDM_FILE_QUIT, HandleQuit)
	ON_COMMAND(IDM_FILE_FIND, HandleFind)
	ON_COMMAND(IDM_FILE_DELETE, HandleDelete)
	ON_COMMAND(IDM_FILE_UNDO, HandleUndo)
	ON_COMMAND(IDM_FILE_DATE, HandleDate)
	ON_COMMAND(IDM_FILE_CUT, HandleCut)
	ON_COMMAND(IDM_FILE_COPY, HandleCopy)
	ON_COMMAND(IDM_FILE_PASTE, HandlePaste)
	ON_COMMAND(IDM_FILE_SAVE, HandleSave)
	ON_COMMAND(IDM_FILE_CLEAR, HandleClear)
	ON_REGISTERED_MESSAGE(findMessage, FindHelper)
	ON_COMMAND(IDM_FILE_ABOUT, HandleAbout)
	ON_WM_MOUSEMOVE() //NO parameter?
	ON_COMMAND(ID_DIRECTORY_TYPE, &CWindow::OnDirectoryType)
	ON_COMMAND(IDM_DIRECTORY_MKDIR, &CWindow::OnDirectoryMkdir)
	ON_COMMAND(ID_DIRECTORY_CHDIR, &CWindow::OnDirectoryChdir)
	ON_COMMAND(IDM_DIRECTORY_RMDIR, &CWindow::OnDirectoryRmdir)
	ON_COMMAND(IDM_DIRECTORY_ATTRIB, &CWindow::OnDirectoryAttrib)
	ON_COMMAND(IDM_DIRECTORY_COPY, &CWindow::OnDirectoryCopy)
	ON_COMMAND(IDM_DIRECTORY_RENAME, &CWindow::OnDirectoryRename)
	ON_COMMAND(IDM_DIRECTORY_CURRENT, &CWindow::OnDirectoryCurrent)
	ON_COMMAND(IDM_DIRECTORY_MOVE, &CWindow::OnDirectoryMove)
	ON_COMMAND(IDM_DIRECTORY_DIREXE, &CWindow::OnDirectoryDirexe)
	ON_COMMAND(IDM_GAME_BATTLEOFFICE, &CWindow::OnGameBattleoffice)
	ON_COMMAND(IDM_GAME_BRAINIAC, &CWindow::OnGameBrainiac)
	ON_COMMAND(IDM_GAME_HENWAY, &CWindow::OnGameHenway)
END_MESSAGE_MAP()

//Initialize the CApp m_pMainWnd data member
BOOL CApp::InitInstance(){
	m_pMainWnd = new CWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return (TRUE);
}

//Create an instance of the application object
CApp App;


UINT CWindow::findMessage = ::RegisterWindowMessage(FINDMSGSTRING); // WHY not inside class???


CWindow::CWindow(){
	CRect rect;
	//int ans = MessageBox(L"Want to Draw? ", L"Do What?", MB_ICONINFORMATION | MB_YESNO);
	//if (ans == IDYES)
		//Create(NULL, L"Drawing", WS_OVERLAPPEDWINDOW, CRect(150, 100, 450, 400));
	//else{
		LoadAccelTable(L"MainAccelTable");
		Create(NULL, L"New OS", WS_OVERLAPPED | WS_SYSMENU, rectDefault);
		menu = new CMenu();
		menu->LoadMenu(L"MainMenu");
		SetMenu(menu);
		DrawMenuBar();
		GetClientRect(&rect);
		m_edit.Create(WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_AUTOHSCROLL | ES_MULTILINE | ES_NOHIDESEL, rect, this, IDC_EDIT);
		m_edit.SetFocus();
	//}
}

void CWindow::OnMouseMove(UINT flag, CPoint mousePos){
	unsigned long seed = time(0);
	srand(seed);

	CClientDC dc(this);
	if (flag == MK_LBUTTON){
		CPoint a[10];

		for (int x = 0; x < 500; x++){
			a[0] = CPoint(rand() % 40, rand() % 100);
			a[1] = CPoint(rand() % 200, rand() % 40);
			a[2] = CPoint(rand() % 200, rand() % 300);
			a[3] = CPoint(rand() % 20, rand() % 20);
			a[4] = CPoint(rand() % 400, rand() % 150);
			a[5] = CPoint(rand() % 100, rand() % 100);

			dc.SetPolyFillMode(ALTERNATE);
			dc.Polygon(a, rand() % 6);
			dc.MoveTo(rand() % 300, rand() % 300);
			dc.LineTo(rand() % 300, rand() % 300);
			CBrush brush(RGB(rand() % 255, rand() % 255, rand() % 255)), *oldBrush;
			oldBrush = dc.SelectObject(&brush);
			dc.ExtFloodFill(100, 100, RGB(rand() % 255, rand() % 255, rand() % 255), FLOODFILLBORDER);
			dc.SelectObject(oldBrush);

		}

		int res = MessageBox(L"Quit", L"Exiting!", MB_ICONQUESTION | MB_YESNO);
		if (res == IDYES)
			DestroyWindow();
	}

	else if (flag == MK_RBUTTON){
		
		for (int x = 0; x < 500; x++){
			CRect rect;
			GetClientRect(&rect);
			CClientDC dc2(this);
			CPen pen(PS_SOLID, rand() % 100, RGB(rand() % 255, rand() % 255, rand() % 255)), *oldPen; //?
			CBrush br(RGB(rand() % 255, rand() % 255, rand() % 255));
			CBrush* pbrOld;
			oldPen = dc2.SelectObject(&pen);
			dc2.Ellipse(rect);
			dc2.SelectObject(oldPen);

			Sleep(500);
		}

		int resp= MessageBox(L"Quit", L"Exiting!", MB_ICONQUESTION | MB_YESNO);
		if (resp == IDYES)
			DestroyWindow();
	}
}

void CWindow::HandleOpen(){
	wchar_t s[200];

	CFileDialog fileDialog(TRUE, fileDialogExt, NULL, OFN_FILEMUSTEXIST, fileDialogFilter);
	if (fileDialog.DoModal() == IDOK){
		cout
			<< "Pathname: " << fileDialog.GetPathName() << endl
			<< "Filename: " << fileDialog.GetFileName() << endl
			<< "Extension: " << fileDialog.GetFileExt() << endl
			<< "File Title: " << fileDialog.GetFileTitle() << endl
			<< endl;

		CStdioFile f;
		CFileException exception;
		BOOL status;
		char name[40];
		char b[65535];//buffer

		for (int a = 0; a < 10000; a++) //flush buffer
			b[a] = ' ';

		int x = 0;
		CString pathString = fileDialog.GetPathName();
		strcpy_s(name, (LPCSTR)pathString.GetString());

		if (_access(name, 04) == 0)
			MessageBox(L"File is there", L"Status", MB_OK);
		try{
			ifstream file(name, ios::binary);
			while (!file.eof()){
				file.read((char*)&b[x++], sizeof(wchar_t));
			}

			file.close();
		}
		catch (...){
			MessageBox(L"File is too big to be loaded\n64K Maximum size \n--Returning!", L"Status", MB_OK);
			m_edit.SetFocus();
			return; 
		}

		status = f.Open(fileDialog.GetPathName(), CFile::modeRead, &exception); 

		if (!status){
			char s[100];
			sprintf_s(s, "Error opening file for reading, Code: %d", exception.m_cause);
			MessageBox((LPCTSTR)s, L"Error", MB_OK);
			return;
		}

		m_edit.SetWindowText((LPCTSTR)b); //SetWindowTextAAAAAAA?
	} //End FileDialog


}

void CWindow::HandleSave(){
	CFile file;
	static CString filePathName;
	CFileDialog fileDialog(FALSE, fileDialogExt, filePathName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, fileDialogFilter);
	if (fileDialog.DoModal() == IDOK){
		CString oldPathName(filePathName); // why need old?
		filePathName = fileDialog.GetPathName();
	}

	wchar_t buffer[65535];
	UINT length = m_edit.GetWindowTextLength();
	if (length == 0){
		MessageBox(L"Nothing to save", L"Warning!", MB_OK);
		m_edit.SetFocus();
		return;
	}

	if (!file.Open(filePathName, CFile::modeCreate | CFile::modeWrite)){
		CString msg("Can't open" + filePathName + "\nCheck the name.");
		MessageBox(msg, L"File Save Error", MB_ICONEXCLAMATION);
		return;
	}

	char info[100];
	sprintf_s(info, "Saving %d Lines", m_edit.GetLineCount()); //sprintf writes into CString/char array
	MessageBox((LPCTSTR)info, L"File save", MB_ICONINFORMATION|MB_OK);
	m_edit.FmtLines(TRUE);
	m_edit.GetWindowText((LPTSTR)buffer, length + 1);
	file.Write(buffer, length + 1);
	file.Close();
	m_edit.SetFocus();
}

void CWindow::HandleClear(){
	UINT length = m_edit.GetWindowTextLength();
	if (length > 0){
		int result = MessageBox(L"Warning: Data Loss! \nProceed", L"Caution", MB_ICONQUESTION | MB_YESNO);
		if (result == IDYES)
			m_edit.SetWindowText(L"");
		m_edit.SetFocus();
	}
}

void CWindow::HandlePrint(){
	CFile f; // ADDED
	char b[10000];
	unsigned int x = 0;
	ofstream printer("PRN"); // ?
	int result = MessageBox(L"Screen File?", L"Print what?", MB_ICONINFORMATION | MB_YESNO);
	if (result == IDYES){
		UINT length = m_edit.GetWindowTextLength();
		m_edit.GetWindowText((LPTSTR)b, length + 1);
		for (x = 0; x < length + 1; x++){
			printer << b[x];
			printer << "\f";
		}
	} // End of print screen
	else{
		wchar_t s[30];
		CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_PAGENUMS | PD_SELECTION);
		if (printDialog.DoModal() == IDOK){
			cout << "Number of Copies: "
				<< printDialog.GetCopies()
				<< endl
				<< endl;
			MessageBox(s, L"Dialog Information", MB_ICONINFORMATION);
			int result = MessageBox(L"Ready to send file to printer", L"File Printing", MB_ICONQUESTION | MB_YESNO);
			if (result == IDYES){
				wchar_t s[200];
				CFileDialog fileDialog(TRUE, fileDialogExt, NULL, OFN_FILEMUSTEXIST, fileDialogFilter);
				if (fileDialog.DoModal() == IDOK){
					cout
						<< "Pathname: " << fileDialog.GetPathName() << endl
						<< "Filename: " << fileDialog.GetFileName() << endl
						<< "Extension: " << fileDialog.GetFileExt() << endl
						<< "File Title: " << fileDialog.GetFileTitle() << endl
						<< endl;
					CFileException exception;
					BOOL status;
					char name[20];
					CString pathname = fileDialog.GetPathName();
					strcpy_s(name, (LPCSTR)pathname.GetString());
					if (_access(name, 04) == 0)
						MessageBox(L"File is there", L"Status", MB_OK);
					ifstream file(name, ios::binary);
					while (!file.eof()){
						file.read((char*)&b[x++], sizeof(char));
					}
					file.close();

					status = f.Open(fileDialog.GetPathName(), CFile::modeRead, &exception); // f or file?
					if (!status){
						char s[100];
						sprintf_s(s, "Error opening file for reading, Code: %d", exception.m_cause);
						MessageBox((LPCTSTR)s, L"Error", MB_OK);
						return;
					}


				} //End if (fileDialog.DoModal() == IDOK)
			} // End MessageBox("Ready to send file to printer", "File Printing", MB_ICONQUESTION | MB_YESNO);

			MessageBox(s, L"Dialog Information", MB_ICONINFORMATION);
			m_edit.SetFocus();
			for (unsigned int z = 0; z < x; z++){
				printer << b[z];
				printer << "\f";
				printer.close();
			}
		} // End if (printDialog.DoModal() == IDOK)
	}// End of print other file
	 // End of if print screen or not
	m_edit.SetFocus();
}

void CWindow::HandleQuit(){

	int answer = MessageBox(L"Do you want to save your file?", L"File Save", MB_ICONQUESTION | MB_YESNO);
	if (answer == IDYES)
		HandleSave();
	int result = MessageBox(L"Are you sure?", L"Exiting!", MB_ICONQUESTION | MB_YESNO);
	if (result == IDYES)
		DestroyWindow();
	else
		m_edit.SetFocus();
}


void CWindow::HandleFind(){ // mondeless box

	findReplaceDialog = new CFindReplaceDialog;
	findReplaceDialog->Create(TRUE, L"default", L"Hanfei");
}

LONG CWindow::FindHelper(UINT WParam, LONG lParam){ // ?? WHY LONG?

	findString.Empty();

	if (findReplaceDialog->IsTerminating())
		findReplaceDialog = NULL;

	else if (findReplaceDialog->FindNext()){
		findString = findReplaceDialog->GetFindString();
		CString line, rightLine;
		int cursorPos, startChar, foundChar, lineIndex, charIndex, lineLength;
		findString.MakeLower();
		lineIndex = m_edit.LineFromChar();
		m_edit.GetSel(startChar, charIndex);

		do{
			lineLength = m_edit.LineLength(charIndex);
			cursorPos = charIndex - m_edit.LineIndex(lineIndex);
			m_edit.GetLine(lineIndex, line.GetBuffer(lineLength), lineLength);
			line.ReleaseBuffer(lineLength);
			rightLine = line.Right(lineLength - cursorPos);
			rightLine.MakeLower();
			foundChar = rightLine.Find(findString);
			if (foundChar == -1)
				charIndex = m_edit.LineIndex(++lineIndex);
		} while ((foundChar == -1) && (lineIndex < m_edit.GetLineCount()));

		if (foundChar != -1){
			startChar = charIndex + foundChar;
			m_edit.SetSel(startChar, startChar + findString.GetLength());
			m_edit.LineScroll(m_edit.LineFromChar(startChar) - m_edit.GetFirstVisibleLine());
			m_edit.SetFocus();
		}
		else {
			if (findReplaceDialog) // ??? !findReplaceDialog?
				findReplaceDialog->EnableWindow(FALSE);
			MessageBox(L"String not found.", L"Find String", MB_ICONINFORMATION);
			if (findReplaceDialog)
				findReplaceDialog->EnableWindow(TRUE);
		}


	}//End of else if (findReplaceDialog->FindNext())

	return 0L;
}


void CWindow::HandleDelete(){
	m_edit.ReplaceSel(L"");
	m_edit.SetFocus();
}

void CWindow::HandleUndo(){
	m_edit.Undo();
	m_edit.SetFocus();
}

void CWindow::HandleCut(){
	m_edit.Cut();
}

void CWindow::HandleCopy(){
	m_edit.Copy();
}

void CWindow::HandlePaste(){
	m_edit.Paste();
}

void CWindow::HandleDate(){
	CTime t;
	t = CTime::GetCurrentTime();
	CString s = t.Format("Current date and time: %c");
	MessageBox(s, L"Date/Time", MB_OK);
	m_edit.SetFocus();
}

void CWindow::HandleAbout(){
	CRect rect;
	CModalDialog aboutDialog(IDM_FILE_ABOUT, this);
	aboutDialog.DoModal();
	m_edit.SetFocus();
}


/////////////////////////////////////////////////////////////////
//// Menu -Directoary
////
void CWindow::OnDirectoryType()
{

	dlgType dlgtype;
	dlgtype.DoModal();

	m_edit.SetWindowTextW(dlgtype.getTextDisplay());
}


void CWindow::OnDirectoryMkdir()
{
	DlgMkdir dlgMkdir;
	dlgMkdir.DoModal();
}


void CWindow::OnDirectoryChdir()
{
	// TODO: Add your command handler code here
}


void CWindow::OnDirectoryRmdir()
{
	DlgRmdir dlgRmdir;
	dlgRmdir.DoModal();
}


void CWindow::OnDirectoryAttrib()
{
	// TODO: Add your command handler code here
}



void CWindow::OnDirectoryCopy()
{
	// TODO: Add your command handler code here
}


void CWindow::OnDirectoryRename()
{
	DlgRename dlgRename;
	dlgRename.DoModal();
}

void CWindow::OnDirectoryMove()
{
	// TODO: Add your command handler code here
}


void CWindow::OnDirectoryCurrent()
{
	// TODO: Add your command handler code here
}

void CWindow::OnDirectoryDirexe(){
	STARTUPINFO sui;
	PROCESS_INFORMATION pi;

	CWindow::setupStartInfo(sui, pi);

	wchar_t LszCommandLine[512] = _T("WinDir");
	wchar_t* pCommandLine = LszCommandLine;
	::CreateProcess(NULL, (LPTSTR)pCommandLine, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &sui, &pi);
}


void CWindow::OnGameBattleoffice()
{
	STARTUPINFO sui;
	PROCESS_INFORMATION pi;
	sui.cb = sizeof(STARTUPINFO);
	sui.lpReserved = 0;
	sui.lpDesktop = NULL;
	sui.lpTitle = NULL;
	sui.dwX = 0;
	sui.dwY = 0;
	sui.dwXSize = 0;
	sui.dwYSize = 0;
	sui.dwXCountChars = 0;
	sui.dwYCountChars = 0;
	sui.dwFillAttribute = 0;
	sui.dwFlags = 0;
	sui.wShowWindow = 0;
	sui.cbReserved2 = 0;
	sui.lpReserved2 = 0;

	wchar_t LszCommandLine[512] = _T("BattleOffice");
	wchar_t* pCommandLine = LszCommandLine;
	::CreateProcess(NULL, (LPTSTR)pCommandLine, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &sui, &pi);
}

void CWindow::OnGameBrainiac(){
	STARTUPINFO sui;
	PROCESS_INFORMATION pi;
	
	CWindow::setupStartInfo(sui, pi);

	wchar_t LszCommandLine[512] = _T("Brainiac 2");
	wchar_t* pCommandLine = LszCommandLine;
	::CreateProcess(NULL, (LPTSTR)pCommandLine, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &sui, &pi);

}

void CWindow::OnGameHenway(){
	STARTUPINFO sui;
	PROCESS_INFORMATION pi;

	CWindow::setupStartInfo(sui, pi);

	wchar_t LszCommandLine[512] = _T("Henway 2");
	wchar_t* pCommandLine = LszCommandLine;
	::CreateProcess(NULL, (LPTSTR)pCommandLine, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &sui, &pi);
}

void CWindow::setupStartInfo(STARTUPINFO & sui, PROCESS_INFORMATION & pi){
	sui.cb = sizeof(STARTUPINFO);
	sui.lpReserved = 0;
	sui.lpDesktop = NULL;
	sui.lpTitle = NULL;
	sui.dwX = 0;
	sui.dwY = 0;
	sui.dwXSize = 0;
	sui.dwYSize = 0;
	sui.dwXCountChars = 0;
	sui.dwYCountChars = 0;
	sui.dwFillAttribute = 0;
	sui.dwFlags = 0;
	sui.wShowWindow = 0;
	sui.cbReserved2 = 0;
	sui.lpReserved2 = 0;
}
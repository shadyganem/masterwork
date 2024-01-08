#include "controller/Clipboard.h"

void mw::Clipboard::CopyTextToClipboard(std::string text)
{
    if (wxTheClipboard->Open())
    {
        // This data objects are held by the clipboard,
        // so do not delete them in the app.
        wxTheClipboard->SetData(new wxTextDataObject(text));
        wxTheClipboard->Close();
    }
}

void mw::Clipboard::CopyTextFromClipboard(std::string& text)
{
    if (wxTheClipboard->Open())
    {
        if (wxTheClipboard->IsSupported(wxDF_TEXT))
        {
            wxTextDataObject data;
            wxTheClipboard->GetData(data);
            text = data.GetText();
        }
        wxTheClipboard->Close();
    }
}

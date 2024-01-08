#pragma once

#include <wx/clipbrd.h>


namespace mw
{
	class Clipboard
	{
		virtual void CopyTextToClipboard(std::string text);
		virtual void CopyTextFromClipboard(std::string& text);
	};
}


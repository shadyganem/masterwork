#pragma once

#include <wx/clipbrd.h>


namespace mw
{
	class Clipboard
	{
	public:
		virtual void CopyTextToClipboard(std::string text);
		virtual void CopyTextFromClipboard(std::string& text);
	};
}


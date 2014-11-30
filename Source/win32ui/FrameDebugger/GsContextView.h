#pragma once

#include "win32/Window.h"
#include "win32/Splitter.h"
#include "win32/Tab.h"
#include "../../GSHandler.h"
#include "../../FrameDump.h"
#include "FrameDebuggerTab.h"
#include "PixelBufferView.h"
#include "GsContextStateView.h"

class CGsContextView : public Framework::Win32::CWindow, public IFrameDebuggerTab
{
public:
													CGsContextView(HWND, const RECT&, CGSHandler*, unsigned int);
	virtual											~CGsContextView();

	void											UpdateState(CGSHandler*, CGsPacketMetadata*, DRAWINGKICK_INFO*) override;

protected:
	long											OnSize(unsigned int, unsigned int, unsigned int) override;
	long											OnCommand(unsigned short, unsigned short, HWND) override;
	long											OnNotify(WPARAM, NMHDR*) override;

private:
	void											UpdateBufferView();
	void											RenderDrawKick(Framework::CBitmap&);

	std::unique_ptr<Framework::Win32::CSplitter>	m_mainSplitter;
	std::unique_ptr<Framework::Win32::CTab>			m_bufferSelectionTab;
	std::unique_ptr<CPixelBufferView>				m_bufferView;
	std::unique_ptr<CGsContextStateView>			m_stateView;

	unsigned int									m_contextId = 0;
	CGSHandler*										m_gs = nullptr;
	DRAWINGKICK_INFO								m_drawingKick;
};

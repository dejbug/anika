#pragma once
#include <windows.h>


template<class Derived>
struct context_t
{
	HWND frame{nullptr};
	multi_tracker_t tracker;

	virtual ~context_t()
	{
	}

	void paint(HDC dc)
	{
		static_cast<Derived *>(this)->paint(dc);
	}

	static LRESULT CALLBACK callback(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		PAINTSTRUCT ps;
		auto ctx = retrieve(h);

		if(ctx) ctx->tracker.callback(h, m, w, l);

		switch(m)
		{
			case WM_ERASEBKGND:
				return 0;

			case WM_PAINT:
				ctx->paint(BeginPaint(h, &ps));
				EndPaint(h, &ps);
				return 0;

			case WM_KEYDOWN:
				switch(w)
				{
					case VK_ESCAPE:
						PostQuitMessage(0);
						break;
				}
				return 0;

			case WM_CLOSE:
				DestroyWindow(h);
				return 0;

			case WM_DESTROY:
				destroy(h);
				return 0;

			case WM_CREATE:
				create(h);
				DragAcceptFiles(h, TRUE);
				return 0;
		}

		return DefWindowProc(h, m, w, l);
	}

	static Derived * create(HWND h)
	{
		auto ctx = new Derived;
		ctx->frame = h;

		SetLastError(0);
		SetWindowLong(h, 0, reinterpret_cast<LONG>(ctx));
		// if(GetLastError()) //... ;

		return ctx;
	}

	static Derived * retrieve(HWND h)
	{
		LONG result = GetWindowLong(h, 0);
		// if(!result) throw error_t;
		return reinterpret_cast<Derived *>(result);
	}

	static void destroy(HWND h)
	{
		auto ctx = retrieve(h);
		if(ctx) delete ctx;
		SetWindowLong(h, 0, 0L);
	}
};

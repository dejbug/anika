#pragma once
#include <windows.h>


template<class Derived>
struct context_t
{
	HWND frame{nullptr};

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
				break;

			case WM_PAINT:
				BeginPaint(h, &ps);
				if(ctx) ctx->paint(ps.hdc);
				EndPaint(h, &ps);
				break;

			case WM_KEYDOWN:
				switch(w)
				{
					case VK_ESCAPE:
						PostQuitMessage(0);
						break;
				}
				break;

			case WM_CLOSE:
				DestroyWindow(h);
				break;

			case WM_DESTROY:
				destroy(h);
				break;

			case WM_CREATE:
				create(h);
				DragAcceptFiles(h, TRUE);
				break;

			default: return DefWindowProc(h, m, w, l);
		}

		return 0;
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

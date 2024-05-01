#include <iostream>
#include <windows.h>
#include <conio.h> 
#include "gui_console.hpp"

namespace gui::console {

	static HANDLE HdConsole = NULL;
	static HWND ConsoleHWND = NULL;
	static va_list FmtVargs = NULL;
	static struct { void* buf; size_t size; } Buffer { nullptr, 0 };
	struct mkcls {
		mkcls(const char* name)    { gui::console::init(name); }
		mkcls(const wchar_t* name) { gui::console::init(name); }
		~mkcls() { gui::console::destroy(); }
	};
	static std::unique_ptr<mkcls> temp = nullptr;

	inline static bool check() {
		return console::ConsoleHWND && console::HdConsole;
	}

	static std::string __make_title_name() {
		CHAR Buffer[MAX_PATH] = "Console for ";
		CHAR* Suffix = Buffer + 0x0C;
		constexpr int MAX_SIZE = MAX_PATH - 0x0C;
		if (GetModuleFileNameA(NULL, Suffix, MAX_SIZE) != NULL) {
			strcpy_s(Suffix, MAX_SIZE, strrchr(Suffix, '\\') + 1);
			*(strrchr(Suffix, '.')) = '\0';
		}
		else {
			strcpy_s(Suffix, MAX_SIZE, "Windows");
		}
		return Buffer;
	}

	static void __Init_Console_Ex() {
		(void)AllocConsole();
		console::HdConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		console::ConsoleHWND = GetConsoleWindow();
		(void)ShowWindow(console::ConsoleHWND, SW_SHOW);
	}

	static void __Clear_Console_Output(CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 }, DWORD cellsWritten = 0) {
		(void)GetConsoleScreenBufferInfo(console::HdConsole, &csbi);
		(void)SetConsoleCursorPosition(console::HdConsole, { 0, 0 });
		(void)FillConsoleOutputCharacter(console::HdConsole, ' ',
			csbi.dwSize.X * csbi.dwSize.Y, { 0, 0 }, &cellsWritten
		);
		(void)FillConsoleOutputAttribute(console::HdConsole, csbi.wAttributes,
			csbi.dwSize.X * csbi.dwSize.Y, { 0, 0 }, &cellsWritten
		);
	}

	void console::init() {
		console::init(console::__make_title_name().c_str());
	}

	void console::init(const char* ConsoleName) {
		console::__Init_Console_Ex();
		(void)SetConsoleTitleA(ConsoleName);
		console::__Clear_Console_Output();
	}

	void console::init(const wchar_t* ConsoleName) {
		if (!console::check()) console::__Init_Console_Ex();
		(void)SetConsoleTitleW(ConsoleName);
		console::__Clear_Console_Output();
	}

	bool console::make() {
		return console::make(console::__make_title_name().c_str());
	}

	bool console::make(const char* name) {
		if (console::temp.get() == nullptr) {
			console::temp = std::make_unique<mkcls>(name);
		}
		return console::temp.get() != nullptr;
	}

	bool console::make(const wchar_t* name) {
		if (console::temp.get() == nullptr) {
			console::temp = std::make_unique<mkcls>(name);
		}
		return console::temp.get() != nullptr;
	}

	void console::destroy() {
		if (console::ConsoleHWND) {
			(void)DestroyWindow(console::ConsoleHWND);
			console::ConsoleHWND = NULL;
		}
		if (console::HdConsole) {
			(void)FreeConsole();
			console::HdConsole = NULL;
		}
		if (console::Buffer.buf) {
			delete[] console::Buffer.buf;
			console::Buffer = { nullptr, 0 };
		}
	}

	static void __Read_Console_asEx(int mode, size_t num) {
	}

	void console::pause() { (void)_getch(); }

	void clear() { console::__Clear_Console_Output(); }

	static void __fmt_write_asEx(const char* fmt, int n_CodePageID, int attrs) {
		if (!console::check() || !console::FmtVargs) return;
		if (int strSz = std::vsnprintf(nullptr, 0, fmt, console::FmtVargs); strSz > 0) {
			if (!console::Buffer.buf || console::Buffer.size <= size_t(strSz)) {
				if (console::Buffer.buf) delete[] console::Buffer.buf;
				console::Buffer = { new char[strSz + 1], size_t(strSz + 1) };
			}
			(void)std::vsnprintf((char*)console::Buffer.buf, console::Buffer.size, fmt, console::FmtVargs);
			if (!strcmp(fmt, "%f") || !strcmp(fmt, "%lf")) {
				char* str = &((char*)console::Buffer.buf)[strSz - 1];
				while (*str == '0') { *str-- = '\0'; }
			}
			SetConsoleTextAttribute(console::HdConsole, attrs);
			UINT o_CodePageID = GetConsoleCP();
			SetConsoleOutputCP(n_CodePageID);
			WriteConsoleA(console::HdConsole, console::Buffer.buf, strSz, NULL, NULL);
			SetConsoleTextAttribute(console::HdConsole, colors::_default);
			SetConsoleOutputCP(o_CodePageID);
		}
	}

	static void __fmt_write_asEx(const wchar_t* fmt, int attrs) {
		if (!console::check() || !console::FmtVargs) return;
		if (int strSz = std::vswprintf(nullptr, 0, fmt, console::FmtVargs); strSz > 0) {
			if (!console::Buffer.buf || (console::Buffer.size / 2) <= size_t(strSz)) {
				if (console::Buffer.buf) delete[] console::Buffer.buf;
				console::Buffer.size = size_t((strSz + 1) * 2);
				console::Buffer.buf = new wchar_t[strSz + 1];
			}
			(void)std::vswprintf((wchar_t*)console::Buffer.buf, console::Buffer.size / 2, fmt, console::FmtVargs);
			if (!wcscmp(fmt, L"%f") || !wcscmp(fmt, L"%lf")) {
				wchar_t* str = &((wchar_t*)console::Buffer.buf)[strSz - 1];
				while (*str == L'0') { *str-- = L'\0'; }
			}
			SetConsoleTextAttribute(console::HdConsole, attrs);
			WriteConsoleW(console::HdConsole, console::Buffer.buf, strSz, NULL, NULL);
			SetConsoleTextAttribute(console::HdConsole, colors::_default);
		}
	}

	void console::write_ex(const char* fmt, int cp, int attrs, ...) {
		__crt_va_start(console::FmtVargs, attrs);
		__fmt_write_asEx(fmt, cp, attrs);
		__crt_va_end(console::FmtVargs);
	}

	void console::fmtwrite(const char* fmt_text, ...) {
		__crt_va_start(console::FmtVargs, fmt_text);
		__fmt_write_asEx(fmt_text, console::cp::_default, colors::_default);
		__crt_va_end(console::FmtVargs);
	}

	void console::fmtcwrite(const char* fmt_text, int attrs, ...) {
		__crt_va_start(console::FmtVargs, attrs);
		__fmt_write_asEx(fmt_text, console::cp::_default, attrs);
		__crt_va_end(console::FmtVargs);
	}

	void console::write(const char* text, int attrs) {
		console::fmtcwrite("%s", attrs, text ? text : "");
	}

	void console::write(const wchar_t* text, int attrs) {
		console::fmtcwrite(L"%s", attrs, text ? text : L"");
	}

	void console::writeline(const char* text, int attrs) {
		console::fmtcwrite("%s\n", attrs, text ? text : "");
	}

	void console::writeline(const wchar_t* text, int attrs) {
		console::fmtcwrite(L"%s\n", attrs, text ? text : L"");
	}

	void console::fmtwrite(const wchar_t* fmt_text, ...) {
		__crt_va_start(console::FmtVargs, fmt_text);
		__fmt_write_asEx(fmt_text, colors::_default);
		__crt_va_end(console::FmtVargs);
	}

	void console::fmtcwrite(const wchar_t* fmt_text, int attrs, ...) {
		__crt_va_start(console::FmtVargs, attrs);
		__fmt_write_asEx(fmt_text, attrs);
		__crt_va_end(console::FmtVargs);
	}
}

namespace gui::console::format {

	void console::format::format_values::_param_write_ex(const param* param, int attr, int enc) {
		switch (param->m_type & 0x0F) {
		case param::flag::int_t:
			console::write<int64_t >(int64_t(param->m_raw.v_int), attr);
			break;
		case param::flag::uint_t:
			console::write<uint64_t>(uint64_t(param->m_raw.v_int), attr);
			break;
		case param::flag::chr_t:
			console::write<char>(char(param->m_raw.v_int), attr);
			break;
		case param::flag::wchr_t:
			console::write<wchar_t>(wchar_t(param->m_raw.v_int), attr);
			break;
		case param::flag::flt_t:
			console::write<double>(double(param->m_raw.v_double), attr);
			break;
		case param::flag::m_str:
			console::write_ex("%s", enc, attr, (char*)(param->m_raw.ptr));
			break;
		case param::flag::w_str:
			console::write<wchar_t*>((wchar_t*)(param->m_raw.ptr), attr);
			break;
		case param::flag::c_val:
			console::write<char*>((char*)(param->m_raw.data), attr);
			break;
		case param::flag::bool_t:
			console::write<bool>(bool(param->m_raw.v_int), attr);
			break;
		case param::flag::ptr_t:
			console::write<void*>((void*)param->m_raw.ptr, attr);
			break;
		default: break;
		}
	}
	bool console::format::formater::is_fmtstr(const param* param) {
		if ((param->m_type & 0x0F) == formater::param::m_str) {

		}
		else if ((param->m_type & 0x0F) == formater::param::w_str){

		}
		return false;
	}

	const console::format::formater::param* console::format::formater::param_at(size_t index) const {
		return index >= this->m_params.count ? nullptr : &this->m_params.array[((this->m_params.count - 1) - index)];
	}

	void console::format::formater::write(const formater& fmt) {
		int attr_value = fmt.m_attrs.value;
		int encode_val = fmt.m_encode.value;
		for (size_t cur = 0; cur < fmt.m_params.count; cur++) {
			const formater::param* param = fmt.param_at(cur);
			if (console::format::formater::is_fmtstr(param)) {

			}
			if ((param->m_type & 0x0F) == formater::param::enc_t) {
				encode_val = int(param->m_raw.v_int);
				continue;
			}
			if ((param->m_type & 0x0F) == formater::param::attr_t) {
				switch (attrs(param->m_raw.v_int)) {
				case formater::un_fcolor:
					attr_value = (fmt.m_attrs.value & 0x0000000F) |
						(attr_value & 0xFFFFFFF0);
					continue;
				case formater::un_bcolor:
					attr_value = (fmt.m_attrs.value & 0x000000F0) |
						(attr_value & 0xFFFFFF0F);
					continue;
				case formater::un_style:
					attr_value = (fmt.m_attrs.value & 0x0000FF00) |
						(attr_value & 0xFFFF00FF);
					continue;
				case formater::un_enc:
					encode_val = fmt.m_encode.value;
					continue;
				case formater::un_attr:
					attr_value = fmt.m_attrs.value;
					continue;
				default: 
					attr_value = int(param->m_raw.v_int);
					continue;
				}
			}
			formater::_param_write_ex(param, attr_value, encode_val);
		}
	}

	void console::format::formater::write(const formater&& fmt) {
		console::format::formater::write(fmt);
	}

}
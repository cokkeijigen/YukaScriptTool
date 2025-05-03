#pragma once

namespace gui::console {

	namespace colors {
		constexpr inline uint16_t dark		  = 0x00;
		constexpr inline uint16_t dark_blue   = 0x01;
		constexpr inline uint16_t dark_green  = 0x02;
		constexpr inline uint16_t dark_teal   = 0x03;
		constexpr inline uint16_t dark_red    = 0x04;
		constexpr inline uint16_t dark_pink   = 0x05;
		constexpr inline uint16_t dark_yellow = 0x06;
		constexpr inline uint16_t dark_white  = 0x07;
		constexpr inline uint16_t dark_gray   = 0x08;
		constexpr inline uint16_t blue        = 0x09;
		constexpr inline uint16_t green       = 0x0A;
		constexpr inline uint16_t teal        = 0x0B;
		constexpr inline uint16_t red         = 0x0C;
		constexpr inline uint16_t pink        = 0x0D;
		constexpr inline uint16_t yellow      = 0x0E;
		constexpr inline uint16_t white       = 0x0F;
		constexpr inline uint16_t _default    = 0x0F;
		namespace back {
			constexpr inline uint16_t dark_blue   = 0x10;
			constexpr inline uint16_t dark_green  = 0x20;
			constexpr inline uint16_t dark_teal   = 0x30;
			constexpr inline uint16_t dark_red    = 0x40;
			constexpr inline uint16_t dark_pink   = 0x50;
			constexpr inline uint16_t dark_yellow = 0x60;
			constexpr inline uint16_t dark_white  = 0x70;
			constexpr inline uint16_t dark_gray   = 0x80;
			constexpr inline uint16_t blue        = 0x90;
			constexpr inline uint16_t green       = 0xA0;
			constexpr inline uint16_t teal        = 0xB0;
			constexpr inline uint16_t red         = 0xC0;
			constexpr inline uint16_t pink        = 0xD0;
			constexpr inline uint16_t yellow      = 0xE0;
			constexpr inline uint16_t white       = 0xF0;
		}
	}

	namespace styles {
		constexpr inline uint16_t lvb_lb = 0x0100;	// COMMON_LVB_LEADING_BYTE
		constexpr inline uint16_t lvb_tb = 0x0200;	// COMMON_LVB_TRAILING_BYTE
		constexpr inline uint16_t lvb_gh = 0x0400;	// COMMON_LVB_GRID_HORIZONTAL
		constexpr inline uint16_t lvb_gl = 0x0800;	// COMMON_LVB_GRID_LVERTICAL
		constexpr inline uint16_t lvb_gr = 0x1000;	// COMMON_LVB_GRID_RVERTICAL
		constexpr inline uint16_t lvb_rv = 0x4000;	// COMMON_LVB_REVERSE_VIDEO
		constexpr inline uint16_t lvb_us = 0x8000;	// COMMON_LVB_UNDERSCORE
	}

	namespace cp {
		constexpr inline int _default = 0;
		constexpr inline int utf_7    = 65000;
		constexpr inline int utf_8    = 65001;
		constexpr inline int sjis     = 932;
		constexpr inline int gbk      = 936;
	}
}

namespace gui::console::format {

	class format_values {
	public:
		enum char_value : char32_t {
			alert = static_cast<char32_t>('\a'),
			space = static_cast<char32_t>(' ' ),
			null  = static_cast<char32_t>('\0'),
			back  = static_cast<char32_t>('\b'),
			feed  = static_cast<char32_t>('\f'),
			endl  = static_cast<char32_t>('\n'),
			begl  = static_cast<char32_t>('\r'),
			htab  = static_cast<char32_t>('\t'),
			vtab  = static_cast<char32_t>('\v'),
			crle  = static_cast<char32_t>('\r\n'),
		};
		enum colors: uint8_t {     dark          = 0x00,
			f_dark_blue   = 0x01,  b_dark_blue   = 0x10,
			f_dark_green  = 0x02,  b_dark_green  = 0x20,
			f_dark_teal   = 0x03,  b_dark_teal   = 0x30,
			f_dark_red    = 0x04,  b_dark_red    = 0x40,
			f_dark_pink   = 0x05,  b_dark_pink   = 0x50,
			f_dark_yellow = 0x06,  b_dark_yellow = 0x60,
			f_dark_white  = 0x07,  b_dark_white  = 0x70,
			f_dark_gray   = 0x08,  b_dark_gray   = 0x80,
			f_blue        = 0x09,  b_blue        = 0x90,
			f_green       = 0x0A,  b_green       = 0xA0,
			f_teal        = 0x0B,  b_teal        = 0xB0,
			f_red         = 0x0C,  b_red         = 0xC0,
			f_pink        = 0x0D,  b_pink        = 0xD0,
			f_yellow      = 0x0E,  b_yellow      = 0xE0,
			f_white       = 0x0F,  b_white       = 0xF0,
		};
		enum styles : uint16_t {
			lvb_lb = 0x0100, lvb_tb = 0x0200, lvb_gh = 0x0400,
			lvb_gl = 0x0800, lvb_gr = 0x1000, lvb_rv = 0x4000,
			lvb_us = 0x8000,
		};

		enum encoding : int {
			utf8 = cp::utf_8, utf7 = cp::utf_7,
			sjis = cp::sjis,  gbk  = cp::gbk,
			ansi = cp::_default, utf16,
			def_encode
		};
		enum attrs : int32_t { 
			def_attr  = 0x0000000F, 
			un_fcolor = 0x1111FFFF,
			un_bcolor = 0x2222FFFF,
			un_style  = 0x3333FFFF,
			un_enc    = 0x4444FFFF,
			un_attr   = 0x5555FFFF,
		};
	protected:
		struct param {
			enum flag: uint8_t {
				m_alloc  = 0x10, int_t  = 0x01, chr_t  = 0x03,
				m_static = 0x20, uint_t = 0x02, wchr_t = 0x04,
				m_str    = 0x06, w_str  = 0x07, attr_t = 0x09,
				flt_t    = 0x05, enc_t  = 0x08, c_val  = 0x0A,
				bool_t   = 0x0B, ptr_t  = 0x0C,
			} m_type = flag(flag::int_t | flag::m_static);

			union {
				const void* ptr; double v_double;
				uint8_t data[8]; uint64_t  v_int; 
			} m_raw = { NULL };

			inline ~param() noexcept;
		};
		static void _param_write_ex(const param*, int, int);
	};

	class formater : public format_values {
		template<typename T> struct is_m_str {
			constexpr static bool const value =
				std::is_same<T, char*>::value || std::is_same<T, char const*>::value;
		};

		template<typename T> struct is_w_str {
			constexpr static bool const value =
				std::is_same<T, wchar_t*>::value || std::is_same<T, wchar_t const*>::value;
		};

		template<typename ...Ts> struct is_attrs_type {
			constexpr static bool const value = (std::is_same<Ts, colors>::value, ...) ||
				(std::is_same<Ts, styles>::value, ...) || (std::is_same<Ts, attrs>::value, ...) ||
				(std::is_same<Ts, encoding>::value, ...);
		};

		template<typename ...Ts> using supp_types =
			typename std::enable_if<is_attrs_type<Ts...>::value, void>::type;
		
	private:
		struct { param* array; size_t count; } m_params = { NULL };
		struct { bool release;  attrs value; } m_attrs  = { NULL };
		struct { bool is_utf16;   int value; } m_encode = { NULL };
		inline formater() { this->m_attrs.value = attrs::def_attr; };
		
		template<size_t index, typename t_value>
		inline void param_add(void* p_value, uint8_t m_type);

		template<typename t_value, typename ...vargs>
		inline bool param_fetch(t_value&& value, vargs&& ...args);

		const param* param_at(size_t index) const;

		static bool is_fmtstr(const param*);
	public:
		static class outputer { static formater out; } out;

		inline ~formater() noexcept;
		inline formater(formater&  copy) noexcept;
		inline formater(formater&& copy) noexcept;

		template<typename ...vargs> inline    formater(vargs&& ...args);
		template<typename ...vargs> static void writes(vargs&& ...args);

		inline static void writes() = delete;
		static void write(const formater&& fmt);
		static void write(const formater&  fmt);

		inline formater& attr(uint16_t value);
		inline formater& set(encoding encode);
		inline formater& set(attrs  attrs);
		inline formater& set(colors color);
		inline formater& set(styles style);
		inline formater& enc(int   encode);
		
		template<class ...vargs, class = supp_types<vargs...>>
		inline formater& set(vargs&& ...args);
	};

	inline formater::colors operator|(formater::colors val1, formater::colors val2) {
		return formater::colors(uint8_t(val1) | uint8_t(val2));
	}

	inline formater::styles operator|(formater::styles val1, formater::styles val2) {
		return formater::styles(uint8_t(val1) | uint8_t(val2));
	}

	inline formater::attrs operator|(formater::styles style, formater::colors color) {
		return formater::attrs(uint32_t(uint16_t(style) << 8 | uint16_t(color)));
	}

	inline formater::attrs operator|(formater::colors color, formater::styles style) {
		return formater::attrs(uint32_t(uint16_t(color) | uint16_t(style) << 8));
	}

	inline formater::attrs operator|(formater::attrs attr, formater::styles style) {
		return formater::attrs(uint32_t(uint16_t(attr) | uint16_t(style) << 8));
	}

	inline formater::attrs operator|(formater::styles style, formater::attrs attr) {
		return formater::attrs(uint32_t(uint16_t(style) << 8 | uint16_t(attr)));
	}

	inline formater::attrs operator|(formater::attrs attr, formater::colors color) {
		return formater::attrs(uint32_t(uint16_t(attr) | uint16_t(color)));
	}

	inline formater::attrs operator|(formater::colors color, formater::attrs attr) {
		return formater::attrs(uint32_t(uint16_t(color) | uint16_t(attr)));
	}

	typedef formater fmt;
}

namespace gui::console {

	extern bool make();

	extern void pause();

	extern void clear();

	extern void init();

	extern void destroy();

	extern bool make(const char*    name);

	extern bool make(const wchar_t* name);

	extern void init(const char*    name);

	extern void init(const wchar_t* name);

	extern void write(const char*    text,  int attrs = colors::_default);

	extern void write(const wchar_t* text,  int attrs = colors::_default);

	extern void writeline(const char*    text, int attrs = colors::_default);

	extern void writeline(const wchar_t* text, int attrs = colors::_default);

	extern void write_ex(const char* fmt, int cp, int attrs, ...);

	extern void fmtwrite(const char*    fmt_text, ...);

	extern void fmtwrite(const wchar_t* fmt_text, ...);

	extern void fmtcwrite(const char*    fmt_text, int attrs, ...);

	extern void fmtcwrite(const wchar_t* fmt_text, int attrs, ...);

	inline void write(format::fmt&  fmt) { format::fmt::write(fmt); }

	inline void write(format::fmt&& fmt) { format::fmt::write(fmt); }

	inline void write(format::fmt::char_value&  c_value, int _ = NULL) {
		console::write(reinterpret_cast<const char*>(&c_value));
	}

	inline void write(format::fmt::char_value&& c_value, int _ = NULL) {
		console::write(reinterpret_cast<const char*>(&c_value));
	}

	inline void writeline() { console::write(format::fmt::endl); }

	namespace __ {
		template <typename T> class c_str {
			template <typename obj> inline static auto fn(void*)
				-> decltype(std::declval<obj>().c_str(), std::true_type()) {
			}
			template <typename obj> inline static std::false_type fn(...) {
			}
		public:
			inline static const bool has = decltype(fn<T>(nullptr))::value;
		};

		template <typename T> class c_string {
			template <typename obj> inline static auto fn(void*)
				-> decltype(std::declval<obj>().string(), std::true_type()) {
			}
			template <typename obj> inline static std::false_type fn(...) {
			}
		public:
			inline static const bool has = decltype(fn<T>(nullptr))::value;
		};

		template <typename T> class c_wstring {
			template <typename obj> inline static auto fn(void*)
				-> decltype(std::declval<obj>().wstring(), std::true_type()) {
			}
			template <typename obj> inline static std::false_type fn(...) {
			}
		public:
			inline static const bool has = decltype(fn<T>(nullptr))::value;
		};

		template <typename T> class to_string {
			template <typename obj> inline static auto fn(void*)
				-> decltype(std::declval<obj>().to_string(), std::true_type()) {
			}
			template <typename obj> inline static std::false_type fn(...) {
			}
		public:
			inline static const bool has = decltype(fn<T>(nullptr))::value;
		};

		template <typename T> class to_wstring {
			template <typename obj> inline static auto fn(void*)
				-> decltype(std::declval<obj>().to_wstring(), std::true_type()) {
			}
			template <typename obj> inline static std::false_type fn(...) {
			}
		public:
			inline static const bool has = decltype(fn<T>(nullptr))::value;
		};

	}

	template<typename t_value> inline void write(t_value&& value, int attrs = colors::_default) {
		if constexpr (std::is_fundamental<std::remove_reference_t<t_value>>::value) {
			if constexpr (std::is_floating_point<typename std::decay<t_value>::type>::value)  {
				gui::console::fmtcwrite("%lf",  attrs, double(value));
			}
			else if constexpr (std::is_same<typename std::decay<t_value>::type, char>::value) {
				gui::console::fmtcwrite("%c",   attrs, char(value));
			}
			else if constexpr (std::is_same<typename std::decay<t_value>::type, wchar_t>::value) {
				gui::console::fmtcwrite(L"%lc", attrs, wchar_t(value));
			}
			else if constexpr (std::is_same<typename std::decay<t_value>::type, bool>::value) {
				gui::console::fmtcwrite("%s", attrs, value ? "true" : "false");
			}
			else if constexpr (std::is_integral<typename std::decay<t_value>::type>::value)   {
				if constexpr (std::is_signed<typename std::decay<t_value>::type>::value) {
					gui::console::fmtcwrite("%lld", attrs, int64_t(value));
				}
				else { 
					gui::console::fmtcwrite("%llu", attrs, uint64_t(value));
				}
			}
			else if constexpr 
			(std::is_same<typename std::decay<t_value>::type, std::nullptr_t>::value) 
			{
				gui::console::write("nullptr", attrs);
			}
		}
		else if constexpr (std::is_enum<typename std::decay<t_value>::type>::value) {
			gui::console::write(static_cast<typename std::underlying_type<
				typename std::decay<t_value>::type>::type>(value));
		}
		else if constexpr (__::to_string<typename std::decay<t_value>::type>::has)  {
			gui::console::write(value.to_string(), attrs);
		}
		else if constexpr (__::to_wstring<typename std::decay<t_value>::type>::has) {
			gui::console::write(value.to_wstring(), attrs);
		}
		else if constexpr (__::c_string<typename std::decay<t_value>::type>::has)   {
			gui::console::write(value.string(), attrs);
		}
		else if constexpr (__::c_wstring<typename std::decay<t_value>::type>::has)  {
			gui::console::write(value.wstring(), attrs);
		}
		else if constexpr (__::c_str<typename std::decay<t_value>::type>::has) {
			gui::console::write(value.c_str(), attrs);
		}
		else if constexpr (std::is_pointer<typename std::decay<t_value>::type>::value) {
			using rawtype = typename std::remove_pointer<typename std::decay<t_value>::type>::type;
			if constexpr (__::c_str<rawtype>::has    || __::to_string<rawtype>::has ||
						  __::c_string<rawtype>::has || __::c_wstring<rawtype>::has ||
				__::to_wstring<rawtype>::has) {
				if (value != nullptr) {
					gui::console::write(std::forward<rawtype&>(*value),    attrs);
				}
				else {
					gui::console::write(static_cast<const void*>(nullptr), attrs);
				}
			}
			else if constexpr (std::is_same<typename std::decay<t_value>::type,    char*>::value) {
				gui::console::write(static_cast<const char*>(value),	attrs);
			}
			else if constexpr (std::is_same<typename std::decay<t_value>::type, wchar_t*>::value) {
				gui::console::write(static_cast<const wchar_t*>(value), attrs);
			}
			else {
				gui::console::fmtcwrite(
					value ? "0x%p" : "nullptr", attrs, static_cast<const void*>(value)
				);
			}
		}
		else {
			static_assert(std::is_pointer<decltype(&value)>::value, "Type not supported!");
			gui::console::write(static_cast<const void*>(&value), attrs);
		}
	}

	template<typename t_value> inline void writeline(t_value&& value, int attrs = colors::_default) {
		gui::console::write(std::forward<t_value>(value), attrs), gui::console::writeline();
	}

	template<typename ...t_value> inline void writelines(t_value&& ...values) {
		(gui::console::writeline(std::forward<t_value&&>(values)), ...);
	}

	template<typename ...t_value> inline void writes(t_value&& ...values) {
		(gui::console::write(std::forward<t_value&&>(values)), ...);
	}

	template<typename ...t_value> inline void pause(t_value&& ...msgs) {
		gui::console::writes(msgs...), gui::console::pause();
	}

}

namespace gui::console::format {

	template<class ...vargs, class>
	inline formater& formater::set(vargs&& ...args) {
		(this->set(args), ...); return *this;
	}

	inline formater& formater::attr(uint16_t value) {
		this->m_attrs.value = attrs(value);
		return *this;
	}

	inline formater& formater::set(formater::encoding encode) {
		this->m_encode = { encode == utf16, encode };
		return *this;
	}

	inline formater& formater::set(formater::attrs  attrs) {
		this->m_attrs.value = attrs;
		return *this;
	}

	inline formater& formater::set(formater::styles style) {
		return this->set(formater::attrs(
			uint16_t(this->m_attrs.value & 0x00FF) | 
			uint16_t(style) << 8
		));
	}

	inline formater& formater::set(formater::colors color) {
		if ((color & 0xF0) && (color && 0x0F)) {
			this->m_attrs.value = formater::attrs(
				(this->m_attrs.value & 0xFF00) | color
			);
		}
		else {
			this->m_attrs.value = formater::attrs(
				(this->m_attrs.value & 
				(color > 0x0F ? 0xFF0F : 0xFFF)) | color
			);
		}
		return *this;
	}

	inline formater& formater::enc(int   encode) {
		this->m_encode = { false, encode };
		return *this;
	}
	
	template<typename ...vargs>  
	static void formater::writes(vargs&& ...args) {
		auto fmt = format::formater();
		fmt.m_params.array = new param[sizeof...(args)];
		fmt.m_params.count = sizeof...(args);
		fmt.param_fetch(std::forward<vargs>(args)...);
		fmt.m_attrs.release = true;
		format::formater::write(fmt);
	}

	template<size_t index, typename t_value>
	inline void formater::param_add(void* p_value, uint8_t m_type) {
		param* param = &this->m_params.array[index];
		if (!std::is_pointer<typename std::decay<t_value>::type>::value) {
			size_t size = sizeof(typename std::decay<t_value>::type);
			memcpy_s(param->m_raw.data, size, p_value, size);
		}
		else {
			param->m_raw.ptr = p_value;
		}
		param->m_type = param::flag(m_type);
	}

	template<typename t_value, typename ...vargs> 
	inline bool formater::param_fetch(t_value&& value, vargs&& ...args) {
		if constexpr (std::is_same<typename std::decay<t_value>::type, char_value>::value) {
			this->param_add<sizeof...(args), t_value>(&value, param::c_val | param::m_static);
		}
		else if constexpr (std::is_fundamental<std::remove_reference_t<t_value>>::value) {
			if constexpr (std::is_floating_point<typename std::decay<t_value>::type>::value) {
				this->param_add<sizeof...(args), t_value>(&value, param::flt_t | param::m_static);
			}
			else if constexpr (std::is_same<typename std::decay<t_value>::type, char>::value) {
				this->param_add<sizeof...(args), t_value>(&value, param::chr_t | param::m_static);
			}
			else if constexpr (std::is_same<typename std::decay<t_value>::type, wchar_t>::value) {
				this->param_add<sizeof...(args), t_value>(&value, param::wchr_t | param::m_static);
			}
			else if constexpr (std::is_same<typename std::decay<t_value>::type, bool>::value) {
				this->param_add<sizeof...(args), t_value>(&value, param::bool_t | param::m_static);
			}
			else if constexpr (std::is_integral<typename std::decay<t_value>::type>::value) {
				constexpr bool is_signed = std::is_signed<typename std::decay<t_value>::type>::value;
				this->param_add<sizeof...(args), t_value>(&value,
					(is_signed ? param::int_t : param::uint_t) | param::m_static);
			}
			else if constexpr (std::is_same<typename std::decay<t_value>::type, std::nullptr_t>::value) {
				return this->param_fetch((const void*)(nullptr), std::forward<vargs>(args)...);
			}
		}
		else if constexpr (is_attrs_type<typename std::decay<t_value>::type>::value) {
			this->param_add<sizeof...(args), t_value>(&value, (std::is_same<typename 
				std::decay<t_value>::type, encoding>::value ? param::enc_t : param::attr_t) 
				| param::m_static
			);
		}
		else if constexpr (std::is_pointer<typename std::decay<t_value>::type>::value) {
			if constexpr (formater::is_m_str<typename std::decay<t_value>::type>::value) {
				if (std::is_rvalue_reference<decltype(value)>::value) {
					size_t strSz = strlen(value); char* buf = new char[strSz + 1];
					strcpy_s(buf, strSz + 1, static_cast<const char*>(value));
					this->param_add<sizeof...(args), void*>(((void*)buf),   param::m_str | param::m_alloc);
				}
				else {
					this->param_add<sizeof...(args), void*>(((void*)value), param::m_str | param::m_static);
				}
			}
			else if constexpr (formater::is_w_str<typename std::decay<t_value>::type>::value) {
				if (std::is_rvalue_reference<decltype(value)>::value) {
					size_t strSz = wcslen(value); wchar_t* buf = new wchar_t[strSz + 1];
					wcscpy_s(buf, strSz + 1, static_cast<const wchar_t*>(value));
					this->param_add<sizeof...(args), void*>(((void*)buf),   param::w_str | param::m_alloc);
				}
				else {
					this->param_add<sizeof...(args), void*>(((void*)value), param::w_str | param::m_static);
				}
			}
			else {
				this->param_add<sizeof...(args), void*>(((void*)value), param::ptr_t | param::m_static);
			}
		}
		else if constexpr (std::is_enum<typename std::decay<t_value>::type>::value) {
			return this->param_fetch(static_cast<typename std::underlying_type
				<typename std::decay<t_value>::type>::type>(value), std::forward<vargs>(args)...);
		}
		else if constexpr (__::to_string<typename std::decay<t_value>::type>::has) {
			return this->param_fetch(
				std::forward<decltype(value.to_string())>(value.to_string()), 
				std::forward<vargs>(args)...
			);
		}
		else if constexpr (__::to_wstring<typename std::decay<t_value>::type>::has) {
			return this->param_fetch(
				std::forward<decltype(value.to_wstring())>(value.to_wstring()),
				std::forward<vargs>(args)...
			);
		}
		else if constexpr (__::c_string<typename std::decay<t_value>::type>::has) {
			return this->param_fetch(
				std::forward<decltype(value.string())>(value.string()),
				std::forward<vargs>(args)...
			);
		}
		else if constexpr (__::c_wstring<typename std::decay<t_value>::type>::has) {
			return this->param_fetch(
				std::forward<decltype(value.wstring())>(value.wstring()),
				std::forward<vargs>(args)...
			);
		}
		else if constexpr (__::c_str<typename std::decay<t_value>::type>::has) {
			return this->param_fetch(
				std::forward<decltype(value.c_str())>(value.c_str()),
				std::forward<vargs>(args)...
			);
		}
		else {
			static_assert(std::is_pointer<decltype(&value)>::value, "Type not supported!");
			this->param_fetch(static_cast<const void*>(&value), std::forward<vargs>(args)...);
		}
		if constexpr (sizeof...(args) > 0) {
			return this->param_fetch(std::forward<vargs>(args)...); 
		}
		return true;
	}

	inline formater::formater(formater&& copy) noexcept: formater(copy) {
	}

	inline formater::formater(formater&  copy) noexcept {
		memcpy_s(this, sizeof(formater), &copy, sizeof(formater));
		copy.m_attrs.release = false;
	}

	template<typename ...vargs> 
	inline formater::formater(vargs&& ...args): formater(){
		this->m_params.array = new param[sizeof...(args)];
		this->m_params.count = sizeof...(args);
		this->param_fetch(std::forward<vargs>(args)...);
		this->m_attrs.release = true;
	}

	inline formater::~formater() noexcept {
		if (this->m_attrs.release && this->m_params.array) {
			delete[] this->m_params.array;
		}
		for (size_t i = 0; i < sizeof(formater); i++) {
			((uint8_t*)this)[i] = 0x00;
		}
	}

	inline formater::param::~param() noexcept {
		if (flag(this->m_type & 0x0F) == flag::m_alloc) {
			if (this->m_raw.ptr != nullptr) {
				delete[] this->m_raw.ptr;
			}
		}
		this->m_raw = { NULL };
	}

}

#define add_code_page_namespace(name, cdpg)                                       \
	namespace gui::console::name {                                                \
		inline void write(const char* text, int attrs = colors::_default) {       \
			gui::console::write_ex("%s", cdpg, attrs, text);					  \
		}                                                                         \
		inline void writeline(const char* text, int attrs = colors::_default) {   \
			gui::console::write_ex("%s\n", cdpg, attrs, text);                    \
		}                                                                         \
		template<typename ...vargs>                                               \
		inline void fmtwrite(const char* fmt, const vargs& ...args) {             \
			gui::console::write_ex(fmt, cdpg, colors::_default, args...);		  \
		}                                                                         \
		template<typename ...vargs>                                               \
		inline void fmtcwrite(const char* fmt, int attrs, const vargs& ...args) { \
			gui::console::write_ex(fmt, cdpg, attrs,  args...);					  \
		}                                                                         \
		template<typename t_value> 												  \
		inline void write(t_value&& value, int attrs = colors::_default) {		  \
			if constexpr (														  \
				std::is_pointer<typename std::decay<t_value>::type>::value		  \
				) {																  \
				using rawtype =													  \
					typename std::remove_pointer<								  \
					typename std::decay<t_value >::type>::type;					  \
				if constexpr (													  \
					__::c_str<rawtype>::has    || __::to_string<rawtype>::has ||  \
					__::c_string<rawtype>::has || __::c_wstring<rawtype>::has ||  \
				__::to_wstring<rawtype>::has) {									  \
					if (value != nullptr) {										  \
						write(std::forward<rawtype>(*value),   attrs);			  \
					}															  \
					else {														  \
						write(static_cast<const void*>(value), attrs);			  \
					}															  \
					return;														  \
				}																  \
			}																	  \
			if constexpr (														  \
				__::to_string<typename std::decay<t_value>::type>::has			  \
				) {																  \
				write(value.to_string(), attrs);							      \
				return;															  \
			}																	  \
			if constexpr (														  \
				__::to_wstring<typename std::decay<t_value>::type>::has			  \
				) {																  \
				write(value.to_wstring(), attrs);							      \
				return;															  \
			}																	  \
			if constexpr (														  \
				__::c_string<typename std::decay<t_value>::type>::has			  \
				) {																  \
				write(value.string(), attrs);								      \
				return;															  \
			}																	  \
			if constexpr (														  \
				__::c_wstring<typename std::decay<t_value>::type>::has			  \
				) {																  \
				write(value.wstring(), attrs);								      \
				return;															  \
			}																	  \
			if constexpr (														  \
				__::c_str<typename std::decay<t_value>::type>::has				  \
				) {																  \
			    write(value.c_str(), attrs);								      \
				return;															  \
			}																	  \
			gui::console::write(value, attrs);									  \
		}																		  \
		template<typename t_value> 												  \
		inline void writeline(t_value&& value, int attrs = colors::_default) {	  \
			write(value, attrs), gui::console::writeline();						  \
		}																		  \
		template<typename ...t_value> 											  \
		inline void writes(t_value&& ...values) {								  \
			(void)std::initializer_list<int>{									  \
				(write(std::forward<t_value>(values)), 0)...					  \
			};																	  \
		}																		  \
		template<typename ...t_value>											  \
		inline void writelines(t_value&& ...values) {							  \
			(void)std::initializer_list<int>{									  \
				(writeline(std::forward<t_value>(values)), 0)...				  \
			};																	  \
		}																		  \
	}

#define add_color_namespace_ex(base, color)                                       \
    namespace base::color {                                                       \
		inline void write(const char* text) {                                     \
			base::write(text, gui::console::colors::color);                       \
		}                                                                         \
		inline void writeline(const char* text) {                                 \
			base::writeline(text, gui::console::colors::color);                   \
		}                                                                         \
		template<typename ...vargs>                                               \
		inline void fmtwrite(const char* fmt_text, const vargs& ... args) {       \
			base::fmtcwrite(fmt_text, gui::console::colors::color, args...);      \
		}                                                                         \
		template<typename t_value> 												  \
		inline void write(t_value&& value) {									  \
			base::write(value, gui::console::colors::color);					  \
		}																		  \
		template<typename t_value>												  \
		inline void writeline(t_value&& value) {								  \
			base::writeline(value, gui::console::colors::color);				  \
		}																		  \
		template<typename ...t_value>											  \
		inline void writes(t_value&& ...values) {								  \
			(void)std::initializer_list<int>{									  \
				(base::write(													  \
					std::forward<t_value>(values),								  \
					gui::console::colors::color									  \
				), 0)...														  \
			};																	  \
		};																		  \
		template<typename ...t_value>											  \
		inline void writelines(t_value&& ...values) {							  \
			(void)std::initializer_list<int>{									  \
				(base::writeline(												  \
					std::forward<t_value>(values),								  \
					gui::console::colors::color									  \
				), 0)...														  \
			};																	  \
		}																		  \
	};

#define add_color_namespace_bs(base, color)                                       \
    namespace base::color {                                                       \
		inline void write(const wchar_t* text) {                                  \
			base::write(text, gui::console::colors::color);                       \
		}                                                                         \
		inline void writeline(const wchar_t* text) {                              \
			base::writeline(text, gui::console::colors::color);                   \
		}                                                                         \
		template<typename ...vargs>                                               \
		inline void write_ex(const char* fmt, int cp, const vargs& ... args) {    \
			base::write_ex(fmt, cp, gui::console::colors::color, args...);        \
		}                                                                         \
		template<typename ...vargs>                                               \
		inline void fmtwrite(const wchar_t* fmt_text, const vargs& ... args) {    \
			base::fmtcwrite(fmt_text, gui::console::colors::color, args...);      \
		}                                                                         \
	};	

#define add_all_color_namespace(namespace_template, base)                         \
		namespace_template(base, dark_blue  )                                     \
		namespace_template(base, dark_green )                                     \
		namespace_template(base, dark_teal  )                                     \
		namespace_template(base, dark_red   )                                     \
		namespace_template(base, dark_pink  )                                     \
		namespace_template(base, dark_yellow)                                     \
		namespace_template(base, dark_white )                                     \
		namespace_template(base, dark_gray  )                                     \
		namespace_template(base, blue		)                                     \
		namespace_template(base, green		)                                     \
		namespace_template(base, teal		)                                     \
		namespace_template(base, red		)                                     \
		namespace_template(base, pink		)                                     \
		namespace_template(base, yellow	    )                                     \
		namespace_template(base, white		) 

add_code_page_namespace(utf8, gui::console::cp::utf_8)
add_code_page_namespace(sjis, gui::console::cp::sjis )
add_code_page_namespace(gbk , gui::console::cp::gbk  )
add_all_color_namespace(add_color_namespace_bs, gui::console)
add_all_color_namespace(add_color_namespace_ex, gui::console)
add_all_color_namespace(add_color_namespace_ex, gui::console::utf8)
add_all_color_namespace(add_color_namespace_ex, gui::console::sjis)
add_all_color_namespace(add_color_namespace_ex, gui::console::gbk )

#undef add_code_page_namespace
#undef add_color_namespace_bs
#undef add_color_namespace_ex
#undef add_all_color_namespace

namespace gui::console::format {

}

#ifdef _DEBUG
/********************* 基础函数 ***********************/

#define logd_make   gui::console::make
#define LOGD_MAKE   gui::console::make
#define logd_init   gui::console::init
#define LOGD_INIT   gui::console::init
#define logd        gui::console::write
#define LOGD        gui::console::write
#define logds       gui::console::writes
#define LOGDS       gui::console::writes
#define logd_ex     gui::console::write_ex 
#define LOGD_EX     gui::console::write_ex
#define logd_ln     gui::console::writeline
#define LOGD_LN     gui::console::writeline
#define logd_lns    gui::console::writelines
#define LOGD_LNS    gui::console::writelines
#define logd_fmt    gui::console::fmtwrite
#define LOGD_FMT    gui::console::fmtwrite
#define logd_fmtc   gui::console::fmtcwrite
#define LOGD_FMTC   gui::console::fmtcwrite
#define logd_detr	gui::console::destroy
#define LOGD_DETR	gui::console::destroy

/******************* UTF8编码拓展 *********************/

#define logd_utf8      gui::console::utf8::write
#define LOGD_UTF8      gui::console::utf8::write
#define logds_utf8     gui::console::utf8::writes
#define LOGDS_UTF8     gui::console::utf8::writes
#define logd_ln_utf8   gui::console::utf8::writeline
#define LOGD_LN_UTF8   gui::console::utf8::writeline
#define logd_lns_utf8  gui::console::utf8::writelines
#define LOGD_LNS_UTF8  gui::console::utf8::writelines
#define logd_fmt_utf8  gui::console::utf8::fmtwrite 
#define LOGD_FMT_UTF8  gui::console::utf8::fmtwrite 
#define logd_fmtc_utf8 gui::console::utf8::fmtcwrite
#define LOGD_FMTC_UTF8 gui::console::utf8::fmtcwrite

/***************** SHIFT-JIS编码拓展 ******************/

#define logd_sjis      gui::console::sjis::write
#define LOGD_SJIS      gui::console::sjis::write
#define logds_sjis     gui::console::sjis::writes
#define LOGDS_SJIS     gui::console::sjis::writes
#define logd_ln_sjis   gui::console::sjis::writeline
#define LOGD_LN_SJIS   gui::console::sjis::writeline
#define logd_lns_sjis  gui::console::sjis::writelines
#define LOGD_LNS_SJIS  gui::console::sjis::writelines
#define logd_fmt_sjis  gui::console::sjis::fmtwrite 
#define LOGD_FMT_SJIS  gui::console::sjis::fmtwrite 
#define logd_fmtc_sjis gui::console::sjis::fmtcwrite
#define LOGD_FMTC_SJIS gui::console::sjis::fmtcwrite

/******************** GBK编码拓展 *********************/

#define logd_gbk      gui::console::gbk::write
#define LOGD_GBK      gui::console::gbk::write
#define logds_gbk     gui::console::gbk::writes
#define LOGDS_GBK     gui::console::gbk::writes
#define logd_ln_gbk   gui::console::gbk::writeline
#define LOGD_LN_GBK   gui::console::gbk::writeline
#define logd_lns_gbk  gui::console::gbk::writelines
#define LOGD_LNS_GBK  gui::console::gbk::writelines
#define logd_fmt_gbk  gui::console::gbk::fmtwrite 
#define LOGD_FMT_GBK  gui::console::gbk::fmtwrite 
#define logd_fmtc_gbk gui::console::gbk::fmtcwrite
#define LOGD_FMTC_GBK gui::console::gbk::fmtcwrite

#else 
/********* 非Debug环境下则不会调用控制台函数 ************/

#define CALLNOP(...) 
#define logd_make      CALLNOP
#define LOGD_MAKE      CALLNOP
#define logd_init      CALLNOP
#define LOGD_INIT      CALLNOP
#define logd_ex        CALLNOP
#define LOGD_EX        CALLNOP
#define logd           CALLNOP
#define LOGD           CALLNOP
#define logd_ln        CALLNOP
#define logd_ln        CALLNOP
#define logd_fmt       CALLNOP
#define LOGD_FMT       CALLNOP
#define logd_fmtc      CALLNOP
#define LOGD_FMTC      CALLNOP
#define logd_detr      CALLNOP
#define LOGD_DETR      CALLNOP
#define logd_utf8	   CALLNOP   
#define LOGD_UTF8	   CALLNOP
#define logds_utf8     CALLNOP
#define LOGDS_UTF8     CALLNOP
#define logd_ln_utf8   CALLNOP
#define LOGD_LN_UTF8   CALLNOP
#define logd_lns_utf8  CALLNOP
#define LOGD_LNS_UTF8  CALLNOP
#define logd_fmt_utf8  CALLNOP
#define LOGD_FMT_UTF8  CALLNOP
#define logd_fmtc_utf8 CALLNOP
#define LOGD_FMTC_UTF8 CALLNOP
#define logd_sjis      CALLNOP
#define LOGD_SJIS      CALLNOP
#define logds_sjis     CALLNOP
#define LOGDS_SJIS     CALLNOP
#define logd_ln_sjis   CALLNOP
#define LOGD_LN_SJIS   CALLNOP
#define logd_lns_sjis  CALLNOP
#define LOGD_LNS_SJIS  CALLNOP
#define logd_fmt_sjis  CALLNOP
#define LOGD_FMT_SJIS  CALLNOP
#define logd_fmtc_sjis CALLNOP
#define LOGD_FMTC_SJIS CALLNOP
#define logd_gbk       CALLNOP
#define LOGD_GBK       CALLNOP
#define logds_gbk      CALLNOP
#define LOGDS_GBK      CALLNOP
#define logd_ln_gbk    CALLNOP
#define LOGD_LN_gbk    CALLNOP
#define logd_lns_gbk   CALLNOP
#define LOGD_LNS_GBK   CALLNOP
#define logd_fmt_gbk   CALLNOP
#define LOGD_FMT_GBK   CALLNOP
#define logd_fmtc_gbk  CALLNOP
#define LOGD_FMTC_GBK  CALLNOP

#endif // DEBUG_OUTPUT_LOGS

#ifdef g_console
#undef g_console
#endif 

#define g_console gui::console
#define lcolor gui::console::colors
#define LCOLOR gui::console::colors
#define _GUI_CONSOLE_
#define _gui_console_
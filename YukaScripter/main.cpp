#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <filesystem>
#include <filetool.h>
#include <windows.h>
#include <strtool.h>
#include <gui_console.hpp>
#include <writebuffer.h>
#define TestPath "D:\\Galgame\\Çç¤ì¥Ï¥ì¤Ï©`¤ì¤à\\yks\\story\\ep00\\"
#define TestPath2 "D:\\Galgame\\Çç¤ì¥Ï¥ì¤Ï©`¤ì¤à\\yks\\"

namespace fsys {

	using namespace std::filesystem;
	using dir_ety = directory_entry;
	using dir_ite = directory_iterator;

	static std::string change(const path& p, std::string ext) noexcept {
		return p.stem().string().append(ext);
	}

	static bool make(const path& p) noexcept {
		return exists(p) || create_directories(p);
	}

	static std::string pcat(path p1, path p2) noexcept {
		return (p1 /= p2).string();
	}

	static void pcat(path p1, path p2, std::string& out) noexcept {
		out.assign(fsys::pcat(p1, p2));
	}

	static std::string extension(const path& p) noexcept {
		std::string ext(p.extension().string());
		transform(ext.begin(), ext.end(), ext.begin(), tolower);
		return ext;
	}

	static std::string parent(const path& p) noexcept {
		return p.parent_path().string();
	}

	static bool del(const path& p) noexcept {
		return !exists(p) || remove_all(p);
	}

	static std::string name(const path& p) noexcept {
		return p.filename().string();
	}

	static std::string parent_name(const path& p) noexcept {
		return p.parent_path().filename().string();
	}
}

namespace yks_scripter {

	namespace {
		struct yks_header
		{
			char magic[8];
			char unknow[8];
			int32_t code_offset;
			int32_t code_count;
			int32_t index_offset;
			int32_t index_count;
			int32_t data_offset;
			int32_t data_length;
		};

		struct data_ele
		{
			int32_t type;
			int32_t data1;
			int32_t data2;
			int32_t data3;
		};

		enum ele_type : int {
			TYPE_FUNC = 0x00,
			TYPE_CTRL = 0x01,
			TYPE_CINT = 0x04,
			TYPE_CSTR = 0x05,
			TYPE_VINT = 0x08,
			TYPE_VSTR = 0x09,
			TYPE_VTMP = 0x0A,
		};
	}

	static file::writebuffer writebuffer;

	bool export_text(const char* in, const char* out) {
		if (file::data data = file::tool::read(in); data.empty()) {
			return false; 
		}
		else {
			yks_scripter::writebuffer.clear();
			yks_header& header = *(yks_header*)data.buffer;
			int32_t* code_arr = (int32_t*)(data.buffer + header.code_offset);
			data_ele* ele_arr = (data_ele*)(data.buffer + header.index_offset);
			const void* data_ptr = data.buffer + header.data_offset;
			for (size_t i = 0, count = 1; i < header.code_count; i++) {
				const data_ele& ele = ele_arr[code_arr[i]];
				if (ele.type != TYPE_FUNC) continue;
				i++;
				char* name = ((char*)data_ptr) + ele.data1;
				if (!strcmp(name, "StrOutNWC")) {
					const data_ele& cstr = ele_arr[code_arr[i += 2]];
					std::string text = strtool::converts(
						((char*)data_ptr) + cstr.data2, 932, CP_UTF8
					);
					writebuffer.fmtwrite(
						"#0x%04X:0x%02X:StrOutNWC: \n", 
						int(header.data_offset + cstr.data2), int(i)
					);
					writebuffer.fmtwrite(u8"¡ï¡ò  %03d  ¡ò¡ï//%s\n", count, text.c_str());
					writebuffer.fmtwrite(u8"¡ï¡ò  %03d  ¡ò¡ï%s\n\n", count, text.c_str());
					count++;
				}
				else if (!strcmp(name, "StrOut")) {
					const data_ele& cstr = ele_arr[code_arr[++i]];
					std::string text = strtool::converts(
						((char*)data_ptr) + cstr.data2, 932, CP_UTF8
					);
					writebuffer.fmtwrite(
						"#0x%04X:0x%02X:StrOut: \n",
						int(header.data_offset + cstr.data2), int(i)
					);
					writebuffer.fmtwrite(u8"¡ï¡ò  %03d  ¡ò¡ï//%s\n", count, text.c_str());
					writebuffer.fmtwrite(u8"¡ï¡ò  %03d  ¡ò¡ï%s\n\n", count, text.c_str());
					count++;
				}
			}
			return writebuffer.save(out);
		}
	}

	inline static void exports_as_afile(fsys::path in, fsys::path out) {
		std::string out_full = fsys::pcat(out, fsys::change(in, ".txt"));
		if (fsys::extension(in) != ".yks" ||!fsys::make(out)) return;
		gui::console::write(fsys::name(in));
		yks_scripter::export_text(in.string().c_str(), out_full.c_str());
		gui::console::writeline(": OK");
	}

	inline static void exports_as_multifile(fsys::path in, fsys::path out, bool first_level = true) {
		for (const fsys::dir_ety& entry : fsys::dir_ite(in)) {
			if (entry.is_directory()) {
				fsys::path new_out = out / (first_level ? "yks_text" : fsys::parent_name(entry.path()));
				yks_scripter::exports_as_multifile(entry.path(), new_out, false);
			}
			else {
				fsys::path new_out = out / fsys::parent_name(entry.path());
				yks_scripter::exports_as_afile(entry.path(), new_out);
			}
		}
	}


}

int main(int argc, char** argv) {
	gui::console::make();
	
	std::string path = argv[0];
	path.assign(
		path.substr(0, path.find_last_of("\\"))
	);
	yks_scripter::exports_as_multifile(TestPath2, path);
	
	gui::console::pause();

	return 0;
}
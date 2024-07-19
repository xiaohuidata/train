// third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_helpers.h
#pragma once

#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/descriptor.pb.h>

namespace google{
namespace protobuf{
namespace compiler{
namespace cpp{

class Formatter{
public:
	explicit Formatter(io::Printer* printer) : printer_(printer) {}
	Formatter(io::Printer* printer, const std::map<std::string, std::string>& vars)
			: printer_(printer), vars_(vars) {}

	template <typename T>
	void Set(const std::string& key, const T& value) {
		vars_[key] = ToString(value);
	}

	void AddMap(const std::map<std::string, std::string>& vars) {
		for (const auto& keyval : vars) vars_[keyval.first] = keyval.second;
	}

	template <typename... Args>
	void operator()(const char* format, const Args&... args) const {
		printer_->FormatInternal({ToString(args)...}, vars_, format);
	}

	void Indent() const { printer_->Indent(); printer_->Indent(); }
	void Outdent() const { printer_->Outdent(); printer_->Outdent(); }

	io::Printer* printer() const { return printer_; }

	class SaveState{
	public:
		explicit SaveState(Formatter* format) : format_(format), vars_(format->vars_) {}
		~SaveState() { format_->vars_.swap(vars_); }

	private:
		Formatter* format_;
		std::map<std::string, std::string> vars_;
	};

private:
	io::Printer* printer_;
	std::map<std::string, std::string> vars_;

	static std::string ToString(const std::string& s) { return s; }
	template<typename I, typename = typename std::enable_if<std::is_integral<I>::value>::type>
	static std::string ToString(I x) {
		return StrCat(x);
	}
	static std::string ToString(strings::Hex x) { return StrCat(x); }
	static std::string ToString(const FieldDescriptor* d) { return Payload(d); }
	static std::string ToString(const Descriptor* d) { return Payload(d); }
	static std::string ToString(const EnumDescriptor* d) { return Payload(d); }
	static std::string ToString(const EnumValueDescriptor* d) { return Payload(d); }
	static std::string ToString(const OneofDescriptor* d) { return Payload(d); }

	template <typename Descriptor>
	static std::string Payload(const Descriptor* descriptor) {
		std::vector<int> path;
		descriptor->GetLocationPath(&path);
		GeneratedCodeInfo::Annotation annotation;
		for (int i = 0; i < path.size(); ++i) {
			annotation.add_path(path[i]);
		}
		annotation.set_source_file(descriptor->file()->name());
		return annotation.SerializeAsString();
	}
};

}
}
}
}

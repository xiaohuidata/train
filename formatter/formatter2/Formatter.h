// third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_helpers.h
#pragma once

#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/descriptor.pb.h>

namespace google{
namespace protobuf{
namespace compiler{
namespace cpp{

class Formatter {
public:
	explicit Formatter(io::Printer* printer) : printer_(printer) {}
	Formatter(io::Printer* printer,	const absl::flat_hash_map<absl::string_view, std::string>& vars)
			: printer_(printer), vars_(vars) {}

	template <typename T>
 	void Set(absl::string_view key, const T& value) {
		vars_[key] = ToString(value);
 	}

	template <typename... Args>
 	void operator()(const char* format, const Args&... args) const {
		printer_->FormatInternal({ToString(args)...}, vars_, format);
	}

	void Indent() const { printer_->Indent(); printer_->Indent(); }
	void Outdent() const { printer_->Outdent(); printer_->Outdent(); }
	io::Printer* printer() const { return printer_; }

	class PROTOC_EXPORT ScopedIndenter {
	public:
		explicit ScopedIndenter(Formatter* format) : format_(format) {
			format_->Indent();
		}
	~ScopedIndenter() { format_->Outdent(); }

	private:
		Formatter* format_;
	};

	PROTOBUF_NODISCARD ScopedIndenter ScopedIndent() {
		return ScopedIndenter(this);
	}
	template <typename... Args>
 	ROTOBUF_NODISCARD ScopedIndenter ScopedIndent(const char* format, const Args&&... args) {
		(*this)(format, static_cast<Args&&>(args)...);
		return ScopedIndenter(this);
 	}

private:
	io::Printer* printer_;
	absl::flat_hash_map<absl::string_view, std::string> vars_;

	// Convenience overloads to accept different types as arguments.
	static std::string ToString(absl::string_view s) { return std::string(s); }
	template <typename I, typename = typename std::enable_if<std::is_integral<I>::value>::type>
	static std::string ToString(I x) {
		return absl::StrCat(x);
	}
	static std::string ToString(absl::Hex x) { return absl::StrCat(x); }
	static std::string ToString(const FieldDescriptor* d) {
		return Payload(d, GeneratedCodeInfo::Annotation::NONE);
	}
	static std::string ToString(const Descriptor* d) {
		return Payload(d, GeneratedCodeInfo::Annotation::NONE);
	}
	static std::string ToString(const EnumDescriptor* d) {
		return Payload(d, GeneratedCodeInfo::Annotation::NONE);
	}
	static std::string ToString(const EnumValueDescriptor* d) {
		return Payload(d, GeneratedCodeInfo::Annotation::NONE);
	}
	static std::string ToString(const OneofDescriptor* d) {
		return Payload(d, GeneratedCodeInfo::Annotation::NONE);
	}
	static std::string ToString(std::tuple<const FieldDescriptor*, GeneratedCodeInfo::Annotation::Semantic> p) {
		return Payload(std::get<0>(p), std::get<1>(p));
	}
	static std::string ToString(std::tuple<const Descriptor*, GeneratedCodeInfo::Annotation::Semantic> p) {
		return Payload(std::get<0>(p), std::get<1>(p));
	}
	static std::string ToString(std::tuple<const EnumDescriptor*, GeneratedCodeInfo::Annotation::Semantic> p) {
		return Payload(std::get<0>(p), std::get<1>(p));
	}
	static std::string ToString(std::tuple<const EnumValueDescriptor*, GeneratedCodeInfo::Annotation::Semantic> p) {
		return Payload(std::get<0>(p), std::get<1>(p));
	}
	static std::string ToString(std::tuple<const OneofDescriptor*, GeneratedCodeInfo::Annotation::Semantic> p) {
		return Payload(std::get<0>(p), std::get<1>(p));
	}

	template <typename Descriptor>
	static std::string Payload(const Descriptor* descriptor, GeneratedCodeInfo::Annotation::Semantic semantic) {
		std::vector<int> path;
		descriptor->GetLocationPath(&path);
		GeneratedCodeInfo::Annotation annotation;
		for (int index : path) {
			annotation.add_path(index);
		}
		annotation.set_source_file(descriptor->file()->name());
		annotation.set_semantic(semantic);
		return annotation.SerializeAsString();
	}
};

}
}
}
}

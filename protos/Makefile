# protobuf.mk

PROTOC = protoc
PROTO_SRC_DIR = .
PROTO_GEN_DIR = ../src/gen
PROTO_FILES = $(wildcard $(PROTO_SRC_DIR)/*.proto)
PROTO_OBJS = $(PROTO_FILES:$(PROTO_SRC_DIR)/%.proto=$(PROTO_GEN_DIR)/%.pb.cc)
 
all-proto: $(PROTO_OBJS)
 
$(PROTO_GEN_DIR)/%.pb.cc: $(PROTO_SRC_DIR)/%.proto
	@mkdir -p $(@D)
	$(PROTOC) --cpp_out=$(PROTO_GEN_DIR) $<
 
clean-proto:
	rm -rf $(PROTO_GEN_DIR)

.PHONY: all-proto clean-proto

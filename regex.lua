local rt = (function()
local module = {}

local bit = require("bit")
local ffi = require("ffi")

local u32 = ffi.typeof("uint32_t")
local u64 = ffi.typeof("uint64_t")
local i64 = ffi.typeof("int64_t")

local math_ceil = math.ceil
local math_floor = math.floor
local to_number = tonumber

local ID_ZERO = i64(0)
local ID_ONE = i64(1)

local function truncate(num)
	if num >= 0 then
		return (math_floor(num))
	else
		return (math_ceil(num))
	end
end

do
	local add = {}
	local sub = {}
	local mul = {}
	local div = {}
	local rem = {}
	local neg = {}
	local min = {}
	local max = {}
	local copysign = {}
	local nearest = {}

	local to_signed = bit.tobit

	local math_abs = math.abs
	local math_min = math.min
	local math_max = math.max

	local RE_INSTANCE = ffi.new([[union {
		double f64;
		struct { int32_t a32, b32; };
	}]])

	local function round(num)
		if num >= 0 then
			return (math_floor(num + 0.5))
		else
			return (math_ceil(num - 0.5))
		end
	end

	function add.i32(lhs, rhs)
		return (to_signed(lhs + rhs))
	end

	function sub.i32(lhs, rhs)
		return (to_signed(lhs - rhs))
	end

	function mul.i32(lhs, rhs)
		return (to_signed(ID_ONE * lhs * rhs))
	end

	function div.i32(lhs, rhs)
		assert(rhs ~= 0, "division by zero")

		return (truncate(lhs / rhs))
	end

	function div.u32(lhs, rhs)
		assert(rhs ~= 0, "division by zero")

		lhs = to_number(u32(lhs))
		rhs = to_number(u32(rhs))

		return (to_signed(math_floor(lhs / rhs)))
	end

	function rem.u32(lhs, rhs)
		assert(rhs ~= 0, "division by zero")

		lhs = to_number(u32(lhs))
		rhs = to_number(u32(rhs))

		return (to_signed(lhs % rhs))
	end

	function div.u64(lhs, rhs)
		assert(rhs ~= 0, "division by zero")

		return (i64(u64(lhs) / u64(rhs)))
	end

	function rem.u64(lhs, rhs)
		assert(rhs ~= 0, "division by zero")

		return (i64(u64(lhs) % u64(rhs)))
	end

	function neg.f32(num)
		return -num
	end

	function min.f32(lhs, rhs)
		if lhs ~= lhs then
			return lhs
		elseif rhs ~= rhs then
			return rhs
		else
			return (math_min(lhs, rhs))
		end
	end

	function max.f32(lhs, rhs)
		if lhs ~= lhs then
			return lhs
		elseif rhs ~= rhs then
			return rhs
		else
			return (math_max(lhs, rhs))
		end
	end

	function copysign.f32(lhs, rhs)
		RE_INSTANCE.f64 = rhs

		if RE_INSTANCE.b32 >= 0 then
			return (math_abs(lhs))
		else
			return -math_abs(lhs)
		end
	end

	function nearest.f32(num)
		local result = round(num)

		if (math_abs(num) + 0.5) % 2 == 1 then
			if result >= 0 then
				result = result - 1
			else
				result = result + 1
			end
		end

		return result
	end

	neg.f64 = neg.f32
	min.f64 = min.f32
	max.f64 = max.f32
	copysign.f64 = copysign.f32
	nearest.f64 = nearest.f32

	module.add = add
	module.sub = sub
	module.mul = mul
	module.div = div
	module.rem = rem
	module.min = min
	module.max = max
	module.neg = neg
	module.copysign = copysign
	module.nearest = nearest
end

do
	local clz = {}
	local ctz = {}
	local popcnt = {}

	local bit_and = bit.band
	local bit_lshift = bit.lshift
	local bit_rshift = bit.rshift

	function clz.i32(num)
		if num == 0 then
			return 32
		end

		local count = 0

		if bit_rshift(num, 16) == 0 then
			num = bit_lshift(num, 16)
			count = count + 16
		end

		if bit_rshift(num, 24) == 0 then
			num = bit_lshift(num, 8)
			count = count + 8
		end

		if bit_rshift(num, 28) == 0 then
			num = bit_lshift(num, 4)
			count = count + 4
		end

		if bit_rshift(num, 30) == 0 then
			num = bit_lshift(num, 2)
			count = count + 2
		end

		if bit_rshift(num, 31) == 0 then
			count = count + 1
		end

		return count
	end

	function ctz.i32(num)
		if num == 0 then
			return 32
		end

		local count = 0

		if bit_lshift(num, 16) == 0 then
			num = bit_rshift(num, 16)
			count = count + 16
		end

		if bit_lshift(num, 24) == 0 then
			num = bit_rshift(num, 8)
			count = count + 8
		end

		if bit_lshift(num, 28) == 0 then
			num = bit_rshift(num, 4)
			count = count + 4
		end

		if bit_lshift(num, 30) == 0 then
			num = bit_rshift(num, 2)
			count = count + 2
		end

		if bit_lshift(num, 31) == 0 then
			count = count + 1
		end

		return count
	end

	function popcnt.i32(num)
		local count = 0

		while num ~= 0 do
			num = bit_and(num, num - 1)
			count = count + 1
		end

		return count
	end

	function clz.i64(num)
		if num == 0 then
			return 64 * ID_ONE
		end

		local count = ID_ZERO

		if bit_rshift(num, 32) == ID_ZERO then
			num = bit_lshift(num, 32)
			count = count + 32
		end

		if bit_rshift(num, 48) == ID_ZERO then
			num = bit_lshift(num, 16)
			count = count + 16
		end

		if bit_rshift(num, 56) == ID_ZERO then
			num = bit_lshift(num, 8)
			count = count + 8
		end

		if bit_rshift(num, 60) == ID_ZERO then
			num = bit_lshift(num, 4)
			count = count + 4
		end

		if bit_rshift(num, 62) == ID_ZERO then
			num = bit_lshift(num, 2)
			count = count + 2
		end

		if bit_rshift(num, 63) == ID_ZERO then
			count = count + ID_ONE
		end

		return count
	end

	function ctz.i64(num)
		if num == 0 then
			return 64 * ID_ONE
		end

		local count = ID_ZERO

		if bit_lshift(num, 32) == ID_ZERO then
			num = bit_rshift(num, 32)
			count = count + 32
		end

		if bit_lshift(num, 48) == ID_ZERO then
			num = bit_rshift(num, 16)
			count = count + 16
		end

		if bit_lshift(num, 56) == ID_ZERO then
			num = bit_rshift(num, 8)
			count = count + 8
		end

		if bit_lshift(num, 60) == ID_ZERO then
			num = bit_rshift(num, 4)
			count = count + 4
		end

		if bit_lshift(num, 62) == ID_ZERO then
			num = bit_rshift(num, 2)
			count = count + 2
		end

		if bit_lshift(num, 63) == ID_ZERO then
			count = count + ID_ONE
		end

		return count
	end

	function popcnt.i64(num)
		local count = ID_ZERO

		while num ~= ID_ZERO do
			num = bit_and(num, num - ID_ONE)
			count = count + ID_ONE
		end

		return count
	end

	module.clz = clz
	module.ctz = ctz
	module.popcnt = popcnt
end

do
	local le = {}
	local lt = {}
	local ge = {}
	local gt = {}

	function le.u32(lhs, rhs)
		return u32(lhs) <= u32(rhs)
	end

	function lt.u32(lhs, rhs)
		return u32(lhs) < u32(rhs)
	end

	function ge.u32(lhs, rhs)
		return u32(lhs) >= u32(rhs)
	end

	function gt.u32(lhs, rhs)
		return u32(lhs) > u32(rhs)
	end

	function le.u64(lhs, rhs)
		return u64(lhs) <= u64(rhs)
	end

	function lt.u64(lhs, rhs)
		return u64(lhs) < u64(rhs)
	end

	function ge.u64(lhs, rhs)
		return u64(lhs) >= u64(rhs)
	end

	function gt.u64(lhs, rhs)
		return u64(lhs) > u64(rhs)
	end

	module.le = le
	module.lt = lt
	module.ge = ge
	module.gt = gt
end

do
	local wrap = {}
	local trunc = {}
	local extend = {}
	local convert = {}
	local promote = {}
	local demote = {}
	local reinterpret = {}

	local bit_and = bit.band

	-- This would surely be an issue in a multi-thread environment...
	-- ... thankfully this isn't one.
	local RE_INSTANCE = ffi.new([[union {
		int32_t i32;
		int64_t i64;
		float f32;
		double f64;
	}]])

	function wrap.i32_i64(num)
		RE_INSTANCE.i64 = num

		return RE_INSTANCE.i32
	end

	trunc.i32_f32 = truncate
	trunc.i32_f64 = truncate
	trunc.i64_f32 = i64
	trunc.i64_f64 = i64
	trunc.u64_f32 = i64
	trunc.u64_f64 = i64
	trunc.f32 = truncate
	trunc.f64 = truncate

	function extend.i32_n8(num)
		num = bit_and(num, 0xFF)

		if num >= 0x80 then
			return num - 0x100
		else
			return num
		end
	end

	function extend.i32_n16(num)
		num = bit_and(num, 0xFFFF)

		if num >= 0x8000 then
			return num - 0x10000
		else
			return num
		end
	end

	function extend.i64_n8(num)
		num = bit_and(num, 0xFF)

		if num >= 0x80 then
			return num - 0x100
		else
			return num
		end
	end

	function extend.i64_n16(num)
		num = bit_and(num, 0xFFFF)

		if num >= 0x8000 then
			return num - 0x10000
		else
			return num
		end
	end

	function extend.i64_n32(num)
		num = bit_and(num, 0xFFFFFFFF)

		if num >= 0x80000000 then
			return num - 0x100000000
		else
			return num
		end
	end

	extend.i64_i32 = i64

	function extend.i64_u32(num)
		RE_INSTANCE.i64 = ID_ZERO
		RE_INSTANCE.i32 = num

		return RE_INSTANCE.i64
	end

	function convert.f32_i32(num)
		return num
	end

	function convert.f32_u32(num)
		return (to_number(u32(num)))
	end

	function convert.f32_u64(num)
		return (to_number(u64(num)))
	end

	function convert.f64_i32(num)
		return num
	end

	function convert.f64_u32(num)
		return (to_number(u32(num)))
	end

	function convert.f64_u64(num)
		return (to_number(u64(num)))
	end

	function demote.f32_f64(num)
		return num
	end

	function promote.f64_f32(num)
		return num
	end

	function reinterpret.i32_f32(num)
		RE_INSTANCE.f32 = num

		return RE_INSTANCE.i32
	end

	function reinterpret.i64_f64(num)
		RE_INSTANCE.f64 = num

		return RE_INSTANCE.i64
	end

	function reinterpret.f32_i32(num)
		RE_INSTANCE.i32 = num

		return RE_INSTANCE.f32
	end

	function reinterpret.f64_i64(num)
		RE_INSTANCE.i64 = num

		return RE_INSTANCE.f64
	end

	module.wrap = wrap
	module.trunc = trunc
	module.extend = extend
	module.convert = convert
	module.demote = demote
	module.promote = promote
	module.reinterpret = reinterpret
end

do
	local load = {}
	local store = {}
	local allocator = {}

	ffi.cdef([[
	union Any {
		int8_t i8;
		int16_t i16;
		int32_t i32;
		int64_t i64;

		uint8_t u8;
		uint16_t u16;
		uint32_t u32;
		uint64_t u64;

		float f32;
		double f64;
	};

	struct Memory {
		uint32_t min;
		uint32_t max;
		union Any *data;
	};

	void *calloc(size_t num, size_t size);
	void *realloc(void *ptr, size_t size);
	void free(void *ptr);
	]])

	local alias_t = ffi.typeof("uint8_t *")
	local any_t = ffi.typeof("union Any *")
	local cast = ffi.cast

	local function by_offset(pointer, offset)
		local aliased = cast(alias_t, pointer)

		return cast(any_t, aliased + offset)
	end

	function load.i32_i8(memory, addr)
		return by_offset(memory.data, addr).i8
	end

	function load.i32_u8(memory, addr)
		return by_offset(memory.data, addr).u8
	end

	function load.i32_i16(memory, addr)
		return by_offset(memory.data, addr).i16
	end

	function load.i32_u16(memory, addr)
		return by_offset(memory.data, addr).u16
	end

	function load.i32(memory, addr)
		return by_offset(memory.data, addr).i32
	end

	function load.i64_i8(memory, addr)
		return (i64(by_offset(memory.data, addr).i8))
	end

	function load.i64_u8(memory, addr)
		return (i64(by_offset(memory.data, addr).u8))
	end

	function load.i64_i16(memory, addr)
		return (i64(by_offset(memory.data, addr).i16))
	end

	function load.i64_u16(memory, addr)
		return (i64(by_offset(memory.data, addr).u16))
	end

	function load.i64_i32(memory, addr)
		return (i64(by_offset(memory.data, addr).i32))
	end

	function load.i64_u32(memory, addr)
		return (i64(by_offset(memory.data, addr).u32))
	end

	function load.i64(memory, addr)
		return by_offset(memory.data, addr).i64
	end

	function load.f32(memory, addr)
		return by_offset(memory.data, addr).f32
	end

	function load.f64(memory, addr)
		return by_offset(memory.data, addr).f64
	end

	function store.i32_n8(memory, addr, value)
		by_offset(memory.data, addr).i8 = value
	end

	function store.i32_n16(memory, addr, value)
		by_offset(memory.data, addr).i16 = value
	end

	function store.i32(memory, addr, value)
		by_offset(memory.data, addr).i32 = value
	end

	function store.i64_n8(memory, addr, value)
		by_offset(memory.data, addr).i8 = value
	end

	function store.i64_n16(memory, addr, value)
		by_offset(memory.data, addr).i16 = value
	end

	function store.i64_n32(memory, addr, value)
		by_offset(memory.data, addr).i32 = value
	end

	function store.i64(memory, addr, value)
		by_offset(memory.data, addr).i64 = value
	end

	function store.f32(memory, addr, value)
		by_offset(memory.data, addr).f32 = value
	end

	function store.f64(memory, addr, value)
		by_offset(memory.data, addr).f64 = value
	end

	function store.string(memory, addr, data, len)
		local start = by_offset(memory.data, addr)

		ffi.copy(start, data, len or #data)
	end

	local WASM_PAGE_SIZE = 65536

	local function finalizer(memory)
		ffi.C.free(memory.data)
	end

	local function grow_unchecked(memory, old, new)
		memory.data = ffi.C.realloc(memory.data, new)

		assert(memory.data ~= nil, "failed to reallocate")

		ffi.fill(by_offset(memory.data, old), new - old, 0)
	end

	function allocator.new(min, max)
		local data = ffi.C.calloc(max, WASM_PAGE_SIZE)

		assert(data ~= nil, "failed to allocate")

		local memory = ffi.new("struct Memory", min, max, data)

		return ffi.gc(memory, finalizer)
	end

	function allocator.grow(memory, num)
		if num == 0 then
			return memory.min
		end

		local old = memory.min
		local new = old + num

		if new > memory.max then
			return -1
		else
			grow_unchecked(memory, old * WASM_PAGE_SIZE, new * WASM_PAGE_SIZE)
			memory.min = new

			return old
		end
	end

	module.load = load
	module.store = store
	module.allocator = allocator
end

return module

end)()
local add_i32 = rt.add.i32 local band_i32 = bit.band local bor_i32 = bit.bor local extend_i64_i32 = rt.extend.i64_i32 local gt_u32 = rt.gt.u32 local load_i32 = rt.load.i32 local load_i64 = rt.load.i64 local store_i32 = rt.store.i32 local store_i64 = rt.store.i64 local sub_i32 = rt.sub.i32 local memory_at_0 local table_new = require("table.new")local FUNC_LIST = table_new(20, 1)local TABLE_LIST = table_new(0, 1)local MEMORY_LIST = table_new(0, 1)local GLOBAL_LIST = table_new(0, 1)FUNC_LIST[4] =--[[ __wasm_call_ctors ]]function()::continue_at_0::end FUNC_LIST[5] =--[[ _start ]]function()local loc_0 = 0 local reg_0 FUNC_LIST[4]()reg_0 = FUNC_LIST[6]()loc_0 = reg_0 FUNC_LIST[12]()if loc_0 == 0 then goto continue_at_1 end FUNC_LIST[10](loc_0 )error("out of code bounds")::continue_at_1::::continue_at_0::end FUNC_LIST[6] =--[[ __original_main ]]function()local loc_0 = 0 local reg_0 loc_0 = 0 reg_0 = loc_0 goto continue_at_0 ::continue_at_0::return reg_0 end FUNC_LIST[7] =--[[ __wasi_fd_close ]]function(param_0)local reg_0 reg_0 = FUNC_LIST[0](param_0 )reg_0 = band_i32(reg_0 , 65535 )::continue_at_0::return reg_0 end FUNC_LIST[8] =--[[ __wasi_fd_seek ]]function(param_0, param_1, param_2, param_3)local reg_0 reg_0 = FUNC_LIST[1](param_0 , param_1 , param_2 , param_3 )reg_0 = band_i32(reg_0 , 65535 )::continue_at_0::return reg_0 end FUNC_LIST[9] =--[[ __wasi_fd_write ]]function(param_0, param_1, param_2, param_3)local reg_0 reg_0 = FUNC_LIST[2](param_0 , param_1 , param_2 , param_3 )reg_0 = band_i32(reg_0 , 65535 )::continue_at_0::return reg_0 end FUNC_LIST[10] =--[[ __wasi_proc_exit ]]function(param_0)FUNC_LIST[3](param_0 )error("out of code bounds")::continue_at_0::end FUNC_LIST[11] =--[[ dummy ]]function()::continue_at_0::end FUNC_LIST[12] =--[[ __wasm_call_dtors ]]function()FUNC_LIST[11]()FUNC_LIST[20]()::continue_at_0::end FUNC_LIST[13] =--[[ close ]]function(param_0)local reg_0 reg_0 = FUNC_LIST[7](param_0 )param_0 = reg_0 if param_0 ~= 0 then goto continue_at_1 end reg_0 = 0 goto continue_at_0 ::continue_at_1::store_i32(memory_at_0, 0 + 1140, param_0 )reg_0 = -1 ::continue_at_0::return reg_0 end FUNC_LIST[14] =--[[ __stdio_close ]]function(param_0)local reg_0 reg_0 = FUNC_LIST[13](load_i32(memory_at_0, param_0 + 56))::continue_at_0::return reg_0 end FUNC_LIST[15] =--[[ writev ]]function(param_0, param_1, param_2)local loc_0, loc_1 = 0, 0 local reg_0 loc_0 = sub_i32(GLOBAL_LIST[0].value , 16 )GLOBAL_LIST[0].value = loc_0 loc_1 = -1 if param_2 > -1 then goto continue_at_2 end store_i32(memory_at_0, 0 + 1140, 28 )goto continue_at_1 ::continue_at_2::reg_0 = FUNC_LIST[9](param_0 , param_1 , param_2 , add_i32(loc_0 , 12 ))param_2 = reg_0 if param_2 == 0 then goto continue_at_3 end store_i32(memory_at_0, 0 + 1140, param_2 )loc_1 = -1 goto continue_at_1 ::continue_at_3::loc_1 = load_i32(memory_at_0, loc_0 + 12)::continue_at_1::GLOBAL_LIST[0].value = add_i32(loc_0 , 16 )reg_0 = loc_1 ::continue_at_0::return reg_0 end FUNC_LIST[16] =--[[ __stdio_write ]]function(param_0, param_1, param_2)local loc_0, loc_1, loc_2, loc_3, loc_4, loc_5, loc_6 = 0, 0, 0, 0, 0, 0, 0 local reg_0, reg_1 loc_0 = sub_i32(GLOBAL_LIST[0].value , 16 )GLOBAL_LIST[0].value = loc_0 store_i32(memory_at_0, loc_0 + 12, param_2 )store_i32(memory_at_0, loc_0 + 8, param_1 )param_1 = load_i32(memory_at_0, param_0 + 24)store_i32(memory_at_0, loc_0 , param_1 )param_1 = sub_i32(load_i32(memory_at_0, param_0 + 20), param_1 )store_i32(memory_at_0, loc_0 + 4, param_1 )loc_1 = 2 loc_2 = add_i32(param_1 , param_2 )reg_1 = FUNC_LIST[15](load_i32(memory_at_0, param_0 + 56), loc_0 , 2 )loc_3 = reg_1 if loc_2 == loc_3 then goto continue_at_2 end param_1 = loc_0 ::continue_at_3::while true do if loc_3 > -1 then goto continue_at_4 end loc_3 = 0 store_i32(memory_at_0, param_0 + 24, 0 )store_i64(memory_at_0, param_0 + 16, 0LL )store_i32(memory_at_0, param_0 , bor_i32(load_i32(memory_at_0, param_0 ), 32 ))if loc_1 == 2 then goto continue_at_1 end loc_3 = sub_i32(param_2 , load_i32(memory_at_0, param_1 + 4))goto continue_at_1 ::continue_at_4::loc_4 = load_i32(memory_at_0, param_1 + 4)loc_5 = (gt_u32(loc_3 , loc_4 )and 1 or 0)loc_6 = (loc_5 ~= 0 and add_i32(param_1 , 8 )or param_1 )loc_4 = sub_i32(loc_3 , (loc_5 ~= 0 and loc_4 or 0 ))store_i32(memory_at_0, loc_6 , add_i32(load_i32(memory_at_0, loc_6 ), loc_4 ))param_1 = (loc_5 ~= 0 and add_i32(param_1 , 12 )or add_i32(param_1 , 4 ))store_i32(memory_at_0, param_1 , sub_i32(load_i32(memory_at_0, param_1 ), loc_4 ))param_1 = loc_6 loc_2 = sub_i32(loc_2 , loc_3 )loc_1 = sub_i32(loc_1 , loc_5 )reg_1 = FUNC_LIST[15](load_i32(memory_at_0, param_0 + 56), loc_6 , loc_1 )loc_3 = reg_1 if loc_2 ~= loc_3 then goto continue_at_3 end break end ::continue_at_2::param_1 = load_i32(memory_at_0, param_0 + 40)store_i32(memory_at_0, param_0 + 24, param_1 )store_i32(memory_at_0, param_0 + 20, param_1 )store_i32(memory_at_0, param_0 + 16, add_i32(param_1 , load_i32(memory_at_0, param_0 + 44)))loc_3 = param_2 ::continue_at_1::GLOBAL_LIST[0].value = add_i32(loc_0 , 16 )reg_0 = loc_3 ::continue_at_0::return reg_0 end FUNC_LIST[17] =--[[ __lseek ]]function(param_0, param_1, param_2)local loc_0 = 0 local reg_0 loc_0 = sub_i32(GLOBAL_LIST[0].value , 16 )GLOBAL_LIST[0].value = loc_0 reg_0 = FUNC_LIST[8](param_0 , param_1 , band_i32(param_2 , 255 ), add_i32(loc_0 , 8 ))param_0 = reg_0 if param_0 == 0 then goto continue_at_2 end store_i32(memory_at_0, 0 + 1140, (param_0 == 76 and 70 or param_0 ))param_1 = -1LL goto continue_at_1 ::continue_at_2::param_1 = load_i64(memory_at_0, loc_0 + 8)::continue_at_1::GLOBAL_LIST[0].value = add_i32(loc_0 , 16 )reg_0 = param_1 ::continue_at_0::return reg_0 end FUNC_LIST[18] =--[[ __stdio_seek ]]function(param_0, param_1, param_2)local reg_0 reg_0 = FUNC_LIST[17](load_i32(memory_at_0, param_0 + 56), param_1 , param_2 )::continue_at_0::return reg_0 end FUNC_LIST[19] =--[[ __ofl_lock ]]function()local reg_0 reg_0 = 1152 ::continue_at_0::return reg_0 end FUNC_LIST[20] =--[[ __stdio_exit ]]function()local loc_0, loc_1, loc_2 = 0, 0, 0 local reg_0 reg_0 = FUNC_LIST[19]()loc_0 = load_i32(memory_at_0, reg_0 )if loc_0 == 0 then goto continue_at_1 end ::continue_at_2::while true do if load_i32(memory_at_0, loc_0 + 20)== load_i32(memory_at_0, loc_0 + 24)then goto continue_at_3 end reg_0 = TABLE_LIST[0].data[load_i32(memory_at_0, loc_0 + 32)](loc_0 , 0 , 0 )::continue_at_3::loc_1 = load_i32(memory_at_0, loc_0 + 4)loc_2 = load_i32(memory_at_0, loc_0 + 8)if loc_1 == loc_2 then goto continue_at_4 end reg_0 = TABLE_LIST[0].data[load_i32(memory_at_0, loc_0 + 36)](loc_0 , extend_i64_i32(sub_i32(loc_1 , loc_2 )), 1 )::continue_at_4::loc_0 = load_i32(memory_at_0, loc_0 + 52)if loc_0 ~= 0 then goto continue_at_2 end break end ::continue_at_1::loc_0 = load_i32(memory_at_0, 0 + 1156)if loc_0 == 0 then goto continue_at_5 end if load_i32(memory_at_0, loc_0 + 20)== load_i32(memory_at_0, loc_0 + 24)then goto continue_at_6 end reg_0 = TABLE_LIST[0].data[load_i32(memory_at_0, loc_0 + 32)](loc_0 , 0 , 0 )::continue_at_6::loc_1 = load_i32(memory_at_0, loc_0 + 4)loc_2 = load_i32(memory_at_0, loc_0 + 8)if loc_1 == loc_2 then goto continue_at_5 end reg_0 = TABLE_LIST[0].data[load_i32(memory_at_0, loc_0 + 36)](loc_0 , extend_i64_i32(sub_i32(loc_1 , loc_2 )), 1 )::continue_at_5::loc_0 = load_i32(memory_at_0, 0 + 1156)if loc_0 == 0 then goto continue_at_7 end if load_i32(memory_at_0, loc_0 + 20)== load_i32(memory_at_0, loc_0 + 24)then goto continue_at_8 end reg_0 = TABLE_LIST[0].data[load_i32(memory_at_0, loc_0 + 32)](loc_0 , 0 , 0 )::continue_at_8::loc_1 = load_i32(memory_at_0, loc_0 + 4)loc_2 = load_i32(memory_at_0, loc_0 + 8)if loc_1 == loc_2 then goto continue_at_7 end reg_0 = TABLE_LIST[0].data[load_i32(memory_at_0, loc_0 + 36)](loc_0 , extend_i64_i32(sub_i32(loc_1 , loc_2 )), 1 )::continue_at_7::loc_0 = load_i32(memory_at_0, 0 + 1136)if loc_0 == 0 then goto continue_at_9 end if load_i32(memory_at_0, loc_0 + 20)== load_i32(memory_at_0, loc_0 + 24)then goto continue_at_10 end reg_0 = TABLE_LIST[0].data[load_i32(memory_at_0, loc_0 + 32)](loc_0 , 0 , 0 )::continue_at_10::loc_1 = load_i32(memory_at_0, loc_0 + 4)loc_2 = load_i32(memory_at_0, loc_0 + 8)if loc_1 == loc_2 then goto continue_at_9 end reg_0 = TABLE_LIST[0].data[load_i32(memory_at_0, loc_0 + 36)](loc_0 , extend_i64_i32(sub_i32(loc_1 , loc_2 )), 1 )::continue_at_9::::continue_at_0::end local function run_init_code()TABLE_LIST[0] = { min = 4, max = 4, data = {} }MEMORY_LIST[0] = rt.allocator.new(2, 65535)GLOBAL_LIST[0] = { value =66704 }do local target = TABLE_LIST[0].data local offset =1 local data = {FUNC_LIST[14],FUNC_LIST[16],FUNC_LIST[18],}table.move(data, 1, #data, offset, target)end rt.store.string(MEMORY_LIST[0],1024 ,"\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x80\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x04\x00\x00")end return function(wasm)FUNC_LIST[0] = wasm["wasi_snapshot_preview1"].func_list["fd_close"]FUNC_LIST[1] = wasm["wasi_snapshot_preview1"].func_list["fd_seek"]FUNC_LIST[2] = wasm["wasi_snapshot_preview1"].func_list["fd_write"]FUNC_LIST[3] = wasm["wasi_snapshot_preview1"].func_list["proc_exit"]run_init_code()memory_at_0 = MEMORY_LIST[0]return {func_list = {["_start"] = FUNC_LIST[5],},table_list = {},memory_list = {["memory"] = MEMORY_LIST[0],},global_list = {},} end 
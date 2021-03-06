from collections import OrderedDict, namedtuple
import bitstruct as bs
from common_structs import Unpacker

'''
Using an OrderedDict because it self documents quite well
'''

'''
JELF Header
FIXED: These fields must NEVER change location
'''
_Jelf_Ehdr_d = OrderedDict()
_Jelf_Ehdr_d['e_ident']          = 't%d' % (6*8) # FIXED: 6 8-bit characters ('\x7fJELF\x00')
_Jelf_Ehdr_d['e_version_major']  = 'u8'          # FIXED: Indicates loader requirements. Major = format change
_Jelf_Ehdr_d['e_version_minor']  = 'u8'          # FIXED: Indicates loader requirements. Minor = export list update.
_Jelf_Ehdr_d['e_version_patch']  = 'u8'          # FIXED: Indicates loader requirements. Patch = bug fixes.
_Jelf_Ehdr_d['e_app_major'] = 'u8'       # FIXED:  
_Jelf_Ehdr_d['e_app_minor'] = 'u8'       # FIXED:
_Jelf_Ehdr_d['e_app_patch'] = 'u8'       # FIXED:
_Jelf_Ehdr_d['e_public_key']     = 'r%d' % 256   # Public Key to verify signature
_Jelf_Ehdr_d['e_signature']      = 'r%d' % 512   # Signature
_Jelf_Ehdr_d['e_entry_index']    = 'u16'
_Jelf_Ehdr_d['e_shnum']          = 'u16'
_Jelf_Ehdr_d['e_coin_purpose']   = 'u32'
_Jelf_Ehdr_d['e_coin_path']      = 'u32'
_Jelf_Ehdr_d['e_bip32key']       = 't%d' % (32*8)
Jelf_Ehdr = Unpacker( 'Jelf_Ehdr', _Jelf_Ehdr_d )

'''
JELF Section Header
'''
_Jelf_Shdr_d = OrderedDict()
_Jelf_Shdr_d['sh_type']      = 'u2'
_Jelf_Shdr_d['sh_flags']     = 'u2'
_Jelf_Shdr_d['sh_size']      = 'u16'
_Jelf_Shdr_d['sh_info']      = 'u12'    # Limits the application to 4096 sections that require allocation
Jelf_Shdr = Unpacker( 'Jelf_Shdr', _Jelf_Shdr_d )

Jelf_SHT_OTHER = 0
Jelf_SHT_RELA = 1
Jelf_SHT_NOBITS = 2
Jelf_SHT_SYMTAB = 3

Jelf_SHF_ALLOC     = 1 << 0
Jelf_SHF_EXECINSTR = 1 << 1

'''
JELF Symbol
'''
_Jelf_Sym_d = OrderedDict()
_Jelf_Sym_d['st_name']    = 'u12'
_Jelf_Sym_d['st_shndx']   = 'u12'
Jelf_Sym = Unpacker( 'Jelf_Sym', _Jelf_Sym_d )

'''
RELA
'''
_Jelf_Rela_d = OrderedDict()
_Jelf_Rela_d['r_offset']  = 'u16'
_Jelf_Rela_d['r_info']    = 'u16'
_Jelf_Rela_d['r_addend']  = 's16'
Jelf_Rela = Unpacker( 'Jelf_Rela', _Jelf_Rela_d )

Jelf_R_XTENSA_NONE       = 0
Jelf_R_XTENSA_32         = 1
Jelf_R_XTENSA_ASM_EXPAND = 2
Jelf_R_XTENSA_SLOT0_OP   = 3

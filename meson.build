project('stm32-bare-metal', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

stm32_linker_script = join_paths(meson.source_root(), 'STM32F103XB_FLASH.ld')
stm32_startup_file = files('startup_stm32f103xb.s')
sources = [stm32_startup_file]

includes = include_directories(
  [
    'inc',
    'CMSIS_STM32F1',
    'FreeRTOS/include',
    'FreeRTOS/portable/GCC/ARM_CM3'
  ]
)

stm32_link_args = ['-T', stm32_linker_script]

add_project_link_arguments(stm32_link_args, language : ['c', 'cpp'])
add_project_arguments('-DSTM32F103xB', language : ['c', 'cpp'])

subdir('src')

exec_name = 'main'
elf_file = exec_name + '.elf'
hex_file = exec_name + '.hex'
bin_file = exec_name + '.bin'

main_exec = executable(elf_file,
  sources,
  stm32_startup_file,
  include_directories: includes,
)

custom_target('size',
  depends : main_exec,
  input : main_exec,
  output : 'fake',
  command : [find_program('size'), '@INPUT@'],
  build_by_default : true
)

custom_target(hex_file,
  depends : main_exec,
  input : main_exec,
  output : hex_file,
  command : [
    find_program('objcopy'),
    '-O', 'ihex', '@INPUT@', '@OUTPUT@'
  ],
  build_by_default : true
)

custom_target(bin_file,
  depends : main_exec,
  input : main_exec,
  output : bin_file,
  command : [
    find_program('objcopy'),
    '-O', 'binary', '-S', '@INPUT@', '@OUTPUT@'
  ],
  build_by_default : true
)

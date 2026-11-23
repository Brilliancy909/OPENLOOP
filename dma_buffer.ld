/**
  ******************************************************************************
  * @file    dma_buffer.ld
  * @brief   用户自有链接器片段脚本：定义 .dma_buffer 输出段
  * @note    将 .dma_buffer 段固定到 D2 SRAM 起始（0x30000000），DMA1/DMA2
  *          无需跨域桥接即可访问。本文件经 CMakeLists.txt 的 "-T" 选项与
  *          CubeMX 生成的 STM32H750XX_FLASH.ld 叠加（GNU ld 允许多个 -T
  *          脚本），主脚本不做任何修改，CubeMX 重新生成代码不会覆盖本文件。
  ******************************************************************************
  */
SECTIONS
{
    .dma_buffer 0x30000000 (NOLOAD) :
    {
        . = ALIGN(32);
        KEEP(*(.dma_buffer))        /* 配合 -Wl,--gc-sections 防裁剪 */
        KEEP(*(.dma_buffer*))
        . = ALIGN(32);
    }
}

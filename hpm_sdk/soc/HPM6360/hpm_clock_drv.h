/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_CLOCK_DRV_H
#define HPM_CLOCK_DRV_H

#include "hpm_common.h"
#include "hpm_sysctl_drv.h"
#include "hpm_csr_drv.h"


/**
 * @brief Error codes for clock driver
 */
enum {
    status_clk_div_invalid = MAKE_STATUS(status_group_clk, 0),
    status_clk_src_invalid = MAKE_STATUS(status_group_clk, 1),
    status_clk_invalid = MAKE_STATUS(status_group_clk, 2),
    status_clk_operation_unsupported = MAKE_STATUS(status_group_clk, 3),
    status_clk_shared_ahb = MAKE_STATUS(status_group_clk, 4),
    status_clk_shared_axi0 = MAKE_STATUS(status_group_clk, 5),
    status_clk_shared_axi1 = MAKE_STATUS(status_group_clk, 6),
    status_clk_shared_axi2 = MAKE_STATUS(status_group_clk, 7),
    status_clk_shared_cpu0 = MAKE_STATUS(status_group_clk, 8),
    status_clk_shared_cpu1 = MAKE_STATUS(status_group_clk, 9),
    status_clk_fixed = MAKE_STATUS(status_group_clk, 10),

};



/**
 * @brief Clock source group definitions
 */
#define CLK_SRC_GROUP_COMMON (0U)
#define CLK_SRC_GROUP_ADC    (1U)
#define CLK_SRC_GROUP_I2S    (2U)
#define CLK_SRC_GROUP_WDG   (3U)
#define CLK_SRC_GROUP_PMIC   (4U)
#define CLK_SRC_GROUP_AHB    (5U)
#define CLK_SRC_GROUP_AXI   (6U)
#define CLK_SRC_GROUP_DAC   (7U)
#define CLK_SRC_GROUP_CPU0   (9U)
#define CLK_SRC_GROUP_SRC    (10U)
#define CLK_SRC_GROUP_PWDG    (11U)
#define CLK_SRC_GROUP_INVALID (15U)

#define MAKE_CLK_SRC(src_grp, index) (((uint8_t)(src_grp)<<4) | (index))
#define GET_CLK_SRC_GROUP(src) (((uint8_t)(src)>>4) & 0x0FU)
#define GET_CLK_SRC_INDEX(src) ((uint8_t)(src) & 0x0FU)

/**
 * @brief Clock source definitions
 */
typedef enum _clock_sources {
    clk_src_osc24m = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 0),
    clk_src_pll0_clk0 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 1),
    clk_src_pll0_clk1 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 2),
    clk_src_pll0_clk2 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 3),
    clk_src_pll1_clk0 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 4),
    clk_src_pll1_clk1 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 5),
    clk_src_pll2_clk0 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 6),
    clk_src_pll2_clk1 = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 7),
    clk_src_osc32k = MAKE_CLK_SRC(CLK_SRC_GROUP_COMMON, 8),

    clk_adc_src_ana0 = MAKE_CLK_SRC(CLK_SRC_GROUP_ADC, 0),
    clk_adc_src_ana1 = MAKE_CLK_SRC(CLK_SRC_GROUP_ADC, 0),
    clk_adc_src_ana2 = MAKE_CLK_SRC(CLK_SRC_GROUP_ADC, 0),
    clk_adc_src_ahb0 = MAKE_CLK_SRC(CLK_SRC_GROUP_ADC, 1),

    clk_dac_src_ana3 = MAKE_CLK_SRC(CLK_SRC_GROUP_DAC, 0),
    clk_dac_src_ahb0 = MAKE_CLK_SRC(CLK_SRC_GROUP_DAC, 1),

    clk_i2s_src_aud0 = MAKE_CLK_SRC(CLK_SRC_GROUP_I2S, 0),
    clk_i2s_src_aud1 = MAKE_CLK_SRC(CLK_SRC_GROUP_I2S, 1),

    clk_wdg_src_ahb0 = MAKE_CLK_SRC(CLK_SRC_GROUP_WDG, 0),
    clk_wdg_src_osc32k = MAKE_CLK_SRC(CLK_SRC_GROUP_WDG, 1),

    clk_pwdg_src_osc24m = MAKE_CLK_SRC(CLK_SRC_GROUP_PWDG, 0),
    clk_pwdg_src_osc32k = MAKE_CLK_SRC(CLK_SRC_GROUP_PWDG, 1),

    clk_src_invalid = MAKE_CLK_SRC(CLK_SRC_GROUP_INVALID, 15),
} clk_src_t;


#define RESOURCE_INVALID (0xFFFFU)
#define RESOURCE_SHARED_PTPC (0xFFFEU)
#define RESOURCE_SHARED_CPU0 (0xFFFDU)

#define GET_CLOCK_SOURCE_FROM_CLK_SRC(clk_src) (clock_source_t)((uint32_t)(clk_src) & 0xFU)

/* Clock NAME related Macros */
#define MAKE_CLOCK_NAME(resource, src_type, node) (((uint32_t)(resource) << 16) | ((uint32_t)(src_type) << 8) | ((uint32_t)node))
#define GET_CLK_SRC_GROUP_FROM_NAME(name)  (((uint32_t)(name) >> 8) & 0xFFUL)
#define GET_CLK_NODE_FROM_NAME(name) ((uint32_t)(name) & 0xFFUL)
#define GET_CLK_RESOURCE_FROM_NAME(name) ((uint32_t)(name) >> 16)

/**
 * @brief Peripheral Clock Type Description
 */
typedef enum _clock_name {
    clock_cpu0 = MAKE_CLOCK_NAME(sysctl_resource_cpu0, CLK_SRC_GROUP_CPU0, clock_node_cpu0),
    clock_mchtmr0 = MAKE_CLOCK_NAME(sysctl_resource_mchtmr0, CLK_SRC_GROUP_COMMON, clock_node_mchtmr0),
    clock_femc = MAKE_CLOCK_NAME(sysctl_resource_femc, CLK_SRC_GROUP_COMMON, clock_node_femc),
    clock_xpi0 = MAKE_CLOCK_NAME(sysctl_resource_xpi0, CLK_SRC_GROUP_COMMON, clock_node_xpi0),
    clock_xpi1 = MAKE_CLOCK_NAME(sysctl_resource_xpi1, CLK_SRC_GROUP_COMMON, clock_node_xpi1),
    clock_gptmr0 = MAKE_CLOCK_NAME(sysctl_resource_gptmr0, CLK_SRC_GROUP_COMMON, clock_node_gptmr0),
    clock_gptmr1 = MAKE_CLOCK_NAME(sysctl_resource_gptmr1, CLK_SRC_GROUP_COMMON, clock_node_gptmr1),
    clock_gptmr2 = MAKE_CLOCK_NAME(sysctl_resource_gptmr2, CLK_SRC_GROUP_COMMON, clock_node_gptmr2),
    clock_gptmr3 = MAKE_CLOCK_NAME(sysctl_resource_gptmr3, CLK_SRC_GROUP_COMMON, clock_node_gptmr3),
    clock_uart0 = MAKE_CLOCK_NAME(sysctl_resource_uart0, CLK_SRC_GROUP_COMMON, clock_node_uart0),
    clock_uart1 = MAKE_CLOCK_NAME(sysctl_resource_uart1, CLK_SRC_GROUP_COMMON, clock_node_uart1),
    clock_uart2 = MAKE_CLOCK_NAME(sysctl_resource_uart2, CLK_SRC_GROUP_COMMON, clock_node_uart2),
    clock_uart3 = MAKE_CLOCK_NAME(sysctl_resource_uart3, CLK_SRC_GROUP_COMMON, clock_node_uart3),
    clock_uart4 = MAKE_CLOCK_NAME(sysctl_resource_uart4, CLK_SRC_GROUP_COMMON, clock_node_uart4),
    clock_uart5 = MAKE_CLOCK_NAME(sysctl_resource_uart5, CLK_SRC_GROUP_COMMON, clock_node_uart5),
    clock_uart6 = MAKE_CLOCK_NAME(sysctl_resource_uart6, CLK_SRC_GROUP_COMMON, clock_node_uart6),
    clock_uart7 = MAKE_CLOCK_NAME(sysctl_resource_uart7, CLK_SRC_GROUP_COMMON, clock_node_uart7),
    clock_i2c0 = MAKE_CLOCK_NAME(sysctl_resource_i2c0, CLK_SRC_GROUP_COMMON, clock_node_i2c0),
    clock_i2c1 = MAKE_CLOCK_NAME(sysctl_resource_i2c1, CLK_SRC_GROUP_COMMON, clock_node_i2c1),
    clock_i2c2 = MAKE_CLOCK_NAME(sysctl_resource_i2c2, CLK_SRC_GROUP_COMMON, clock_node_i2c2),
    clock_i2c3 = MAKE_CLOCK_NAME(sysctl_resource_i2c3, CLK_SRC_GROUP_COMMON, clock_node_i2c3),
    clock_spi0 = MAKE_CLOCK_NAME(sysctl_resource_spi0, CLK_SRC_GROUP_COMMON, clock_node_spi0),
    clock_spi1 = MAKE_CLOCK_NAME(sysctl_resource_spi1, CLK_SRC_GROUP_COMMON, clock_node_spi1),
    clock_spi2 = MAKE_CLOCK_NAME(sysctl_resource_spi2, CLK_SRC_GROUP_COMMON, clock_node_spi2),
    clock_spi3 = MAKE_CLOCK_NAME(sysctl_resource_spi3, CLK_SRC_GROUP_COMMON, clock_node_spi3),
    clock_can0 = MAKE_CLOCK_NAME(sysctl_resource_can0, CLK_SRC_GROUP_COMMON, clock_node_can0),
    clock_can1 = MAKE_CLOCK_NAME(sysctl_resource_can1, CLK_SRC_GROUP_COMMON, clock_node_can1),
    clock_sdxc0 = MAKE_CLOCK_NAME(sysctl_resource_sdxc0, CLK_SRC_GROUP_COMMON, clock_node_sdxc0),
    clock_ntmr0 = MAKE_CLOCK_NAME(sysctl_resource_ntmr0, CLK_SRC_GROUP_COMMON, clock_node_ntmr0),
    clock_ahb = MAKE_CLOCK_NAME(RESOURCE_SHARED_CPU0, CLK_SRC_GROUP_AHB, clock_node_ahb),
    clock_axi = MAKE_CLOCK_NAME(RESOURCE_SHARED_CPU0, CLK_SRC_GROUP_AXI, clock_node_axi),
    clock_axic = MAKE_CLOCK_NAME(sysctl_resource_axic, CLK_SRC_GROUP_AXI, clock_node_axi),
    clock_axis = MAKE_CLOCK_NAME(sysctl_resource_axis, CLK_SRC_GROUP_AXI, clock_node_axi),
    clock_ahbp = MAKE_CLOCK_NAME(sysctl_resource_ahbp, CLK_SRC_GROUP_AHB, clock_node_ahb),

    clock_ptpc = MAKE_CLOCK_NAME(sysctl_resource_ptpc, CLK_SRC_GROUP_COMMON, clock_node_ptpc),
    clock_ptp0 = MAKE_CLOCK_NAME(RESOURCE_SHARED_PTPC, CLK_SRC_GROUP_COMMON, clock_node_ptp0),
    clock_ref0 = MAKE_CLOCK_NAME(sysctl_resource_ref0, CLK_SRC_GROUP_COMMON, clock_node_ref0),
    clock_ref1 = MAKE_CLOCK_NAME(sysctl_resource_ref1, CLK_SRC_GROUP_COMMON, clock_node_ref0),
    clock_watchdog0 = MAKE_CLOCK_NAME(sysctl_resource_wdg0, CLK_SRC_GROUP_WDG, 0),
    clock_watchdog1 = MAKE_CLOCK_NAME(sysctl_resource_wdg1, CLK_SRC_GROUP_WDG, 1),
    clock_puart = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_PMIC, 0),
    clock_pwdg = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_PWDG, 0),
    clock_eth0 = MAKE_CLOCK_NAME(sysctl_resource_eth0, CLK_SRC_GROUP_COMMON, clock_node_eth0),
    clock_sdp = MAKE_CLOCK_NAME(sysctl_resource_sdp0, CLK_SRC_GROUP_AXI, 0),
    clock_xdma = MAKE_CLOCK_NAME(sysctl_resource_dma1, CLK_SRC_GROUP_AXI, 1),
    clock_rom = MAKE_CLOCK_NAME(sysctl_resource_rom0, CLK_SRC_GROUP_AXI, 2),
    clock_ram0 = MAKE_CLOCK_NAME(sysctl_resource_ram0, CLK_SRC_GROUP_AXI, 3),
    clock_usb0 = MAKE_CLOCK_NAME(sysctl_resource_usb0, CLK_SRC_GROUP_AXI, 4),
    clock_kman = MAKE_CLOCK_NAME(sysctl_resource_kman, CLK_SRC_GROUP_AHB, 0),
    clock_gpio = MAKE_CLOCK_NAME(sysctl_resource_gpio, CLK_SRC_GROUP_AHB, 1),
    clock_mbx0 = MAKE_CLOCK_NAME(sysctl_resource_mbx0, CLK_SRC_GROUP_AHB, 2),
    clock_hdma = MAKE_CLOCK_NAME(sysctl_resource_dma0, CLK_SRC_GROUP_AHB, 4),
    clock_rng = MAKE_CLOCK_NAME(sysctl_resource_rng0, CLK_SRC_GROUP_AHB, 5),
    clock_mot0 = MAKE_CLOCK_NAME(sysctl_resource_mot0, CLK_SRC_GROUP_AHB, 6),
    clock_mot1 = MAKE_CLOCK_NAME(sysctl_resource_mot1, CLK_SRC_GROUP_AHB, 7),
    clock_acmp = MAKE_CLOCK_NAME(sysctl_resource_acmp, CLK_SRC_GROUP_AHB, 10),
    clock_pdm = MAKE_CLOCK_NAME(sysctl_resource_i2spdm0, CLK_SRC_GROUP_I2S, 0),
    clock_dao = MAKE_CLOCK_NAME(sysctl_resource_i2sdao, CLK_SRC_GROUP_I2S, 1),
    clock_msyn = MAKE_CLOCK_NAME(sysctl_resource_msyn, CLK_SRC_GROUP_AHB, 13),
    clock_ffa0 = MAKE_CLOCK_NAME(sysctl_resource_ffa0, CLK_SRC_GROUP_AHB, 14),
    clock_lmm0 = MAKE_CLOCK_NAME(sysctl_resource_lmm0, CLK_SRC_GROUP_CPU0, 0),
    clock_tsns = MAKE_CLOCK_NAME(sysctl_resource_tsns, CLK_SRC_GROUP_CPU0, 0),


    /* For ADC, there are 2-stage clock source and divider configurations */
    clock_ana0 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_ana0),
    clock_ana1 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_ana1),
    clock_ana2 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_ana2),
    clock_adc0 = MAKE_CLOCK_NAME(sysctl_resource_adc0, CLK_SRC_GROUP_ADC, 0),
    clock_adc1 = MAKE_CLOCK_NAME(sysctl_resource_adc1, CLK_SRC_GROUP_ADC, 1),
    clock_adc2 = MAKE_CLOCK_NAME(sysctl_resource_adc2, CLK_SRC_GROUP_ADC, 2),

    /* For DAC, there are 2-stage clock source and divider configurations */
    clock_ana3 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_ana3),
    clock_dac0 = MAKE_CLOCK_NAME(sysctl_resource_dac0, CLK_SRC_GROUP_DAC, 0),

    /* For I2S, there are 2-stage clock source and divider configurations */
    clock_aud0 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_aud0),
    clock_aud1 = MAKE_CLOCK_NAME(RESOURCE_INVALID, CLK_SRC_GROUP_COMMON, clock_node_aud1),
    clock_i2s0 = MAKE_CLOCK_NAME(sysctl_resource_i2s0, CLK_SRC_GROUP_I2S, 0),
    clock_i2s1 = MAKE_CLOCK_NAME(sysctl_resource_i2s1, CLK_SRC_GROUP_I2S, 1),

    /* Clock sources */
    clk_osc0clk0 = MAKE_CLOCK_NAME(sysctl_resource_xtal, CLK_SRC_GROUP_SRC, 0),
    clk_pll0clk0 = MAKE_CLOCK_NAME(sysctl_resource_clk0_pll1, CLK_SRC_GROUP_SRC, 1),
    clk_pll0clk1 = MAKE_CLOCK_NAME(sysctl_resource_clk1_pll0, CLK_SRC_GROUP_SRC, 2),
    clk_pll0clk2 = MAKE_CLOCK_NAME(sysctl_resource_clk2_pll0, CLK_SRC_GROUP_SRC, 3),
    clk_pll1clk0 = MAKE_CLOCK_NAME(sysctl_resource_clk0_pll1, CLK_SRC_GROUP_SRC, 4),
    clk_pll1clk1 = MAKE_CLOCK_NAME(sysctl_resource_clk1_pll1, CLK_SRC_GROUP_SRC, 5),
    clk_pll2clk0 = MAKE_CLOCK_NAME(sysctl_resource_clk0_pll2, CLK_SRC_GROUP_SRC, 6),
    clk_pll2clk1 = MAKE_CLOCK_NAME(sysctl_resource_clk1_pll2, CLK_SRC_GROUP_SRC, 7),
} clock_name_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get specified IP frequency
 * @param[in] clock_name IP clock name
 *
 * @return IP clock frequency in Hz
 */
uint32_t clock_get_frequency(clock_name_t clock_name);


/**
 * @brief Get Clock frequency for selected clock source
 * @param [in] source clock source
 * @return clock frequency for selected clock source
 */
uint32_t get_frequency_for_source(clock_source_t source);

/**
 * @brief Get the IP clock source
 *        Note: This API return the direct clock source
 * @param [in] clock_name clock name
 * @return IP clock source
 */
clk_src_t clock_get_source(clock_name_t clock_name);

/**
 * @brief Set ADC clock source
 * @param[in] clock_name ADC clock name
 * @param[in] src ADC clock source
 *
 * @return #status_success Setting ADC clock source is successful
 *         #status_clk_invalid Invalid ADC clock
 *         #status_clk_src_invalid Invalid ADC clock source
 */
hpm_stat_t clock_set_adc_source(clock_name_t clock_name, clk_src_t src);

/**
 * @brief Set DAC clock source
 * @param[in] clock_name DAC clock name
 * @param[in] src DAC clock source
 *
 * @return #status_success Setting DAC clock source is successful
 *         #status_clk_invalid Invalid DAC clock
 *         #status_clk_src_invalid Invalid DAC clock source
 */
hpm_stat_t clock_set_dac_source(clock_name_t clock_name, clk_src_t src);

/**
 * @brief Set I2S clock source
 * @param[in] clock_name I2S clock name
 * @param[in] src I2S clock source
 *
 * @return #status_success Setting I2S clock source is successful
 *         #status_clk_invalid Invalid I2S clock
 *         #status_clk_src_invalid Invalid I2S clock source
 */
hpm_stat_t clock_set_i2s_source(clock_name_t clock_name, clk_src_t src);

/**
 * @brief Set the IP clock source and divider
 * @param[in] clock_name clock name
 * @param[in] src clock source
 * @param[in] div clock divider, valid range (1 - 256)
 *
 * @return #status_success Setting Clock source and divider is successful.
 *         #status_clk_src_invalid clock source is invalid.
 *         #status_clk_fixed clock source and divider is a fixed value
 *         #status_clk_shared_ahb Clock is shared with the AHB clock
 *         #status_clk_shared_axi0 Clock is shared with the AXI0 clock
 *         #status_clk_shared_axi1 CLock is shared with the AXI1 clock
 *         #status_clk_shared_axi2 Clock is shared with the AXI2 clock
 *         #status_clk_shared_cpu0 Clock is shared with the CPU0 clock
 *         #status_clk_shared_cpu1 Clock is shared with the CPU1 clock
 */
hpm_stat_t clock_set_source_divider(clock_name_t clock_name, clk_src_t src, uint32_t div);

/**
 * @brief Enable IP clock
 * @param[in] clock_name IP clock name
 */
void clock_enable(clock_name_t clock_name);

/**
 * @brief Disable IP clock
 * @param[in] clock_name IP clock name
 */
void clock_disable(clock_name_t clock_name);

/**
 * @brief Add IP to specified group
 * @param[in] clock_name IP clock name
 * @param[in] group resource group index, valid value: 0/1/2/3
 */
void clock_add_to_group(clock_name_t clock_name, uint32_t group);

/**
 * @brief Remove IP from specified group
 * @param[in] clock_name IP clock name
 * @param[in] group resource group index, valid value: 0/1/2/3
 */
void clock_remove_from_group(clock_name_t clock_name, uint32_t group);

/**
 * @brief Check IP in specified group
 * @param[in] clock_name IP clock name
 * @return true if in group, false if not in group
 */
bool clock_check_in_group(clock_name_t clock_name, uint32_t group);

/**
 * @brief Disconnect the clock group from specified CPU
 * @param[in] group clock group index, value value is 0/1/2/3
 * @param[in] cpu CPU index, valid value is 0/1
 */
void clock_connect_group_to_cpu(uint32_t group, uint32_t cpu);

/**
 * @brief Disconnect the clock group from specified CPU
 * @param[in] group clock group index, value value is 0/1/2/3
 * @param[in] cpu CPU index, valid value is 0/1
 */
void clock_disconnect_group_from_cpu(uint32_t group, uint32_t cpu);

/**
 * @brief Delay specified microseconds
 *
 * @param [in] us expected delay interval in microseconds
 */
void clock_cpu_delay_us(uint32_t us);

/**
 * @brief Delay specified milliseconds
 *
 * @param [in] ms expected delay interval in milliseconds
 */
void clock_cpu_delay_ms(uint32_t ms);

/**
 * @brief Update the Core clock frequency
 */
void clock_update_core_clock(void);

/**
 * @brief HPM Core clock variable
 */
extern uint32_t hpm_core_clock;

#ifdef __cplusplus
}
#endif

#endif /* HPM_CLOCK_DRV_H */

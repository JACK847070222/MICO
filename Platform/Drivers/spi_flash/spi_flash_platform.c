/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#include "spi_flash_platform_interface.h"
#include "MicoPlatform.h"

#if defined ( USE_MICO_SPI_FLASH )

extern const mico_spi_device_t  mico_spi_flash;
extern const platform_spi_t     spi_flash_spi;
extern const platform_gpio_t    spi_flash_spi_pins[];

int sflash_platform_init ( /*@shared@*/ void* peripheral_id, /*@out@*/ void** platform_peripheral_out )
{
    UNUSED_PARAMETER( peripheral_id );  /* Unused due to single SPI Flash */

    platform_spi_config_t config;

    config.chip_select = &spi_flash_spi_pins[mico_spi_flash.chip_select];
    config.speed       = mico_spi_flash.speed;
    config.mode        = mico_spi_flash.mode;
    config.bits        = mico_spi_flash.bits;
  
    if ( kNoErr != platform_spi_init( &spi_flash_spi, &config ) )
    {
        /*@-mustdefine@*/ /* Lint: failed - do not define platform peripheral */
        return -1;
        /*@+mustdefine@*/
    }

    *platform_peripheral_out = NULL;

    return 0;
}


extern int sflash_platform_send_recv ( const void* platform_peripheral, /*@in@*/ /*@out@*/ sflash_platform_message_segment_t* segments, unsigned int num_segments  )
{
    UNUSED_PARAMETER( platform_peripheral );

    platform_spi_config_t config;

    config.chip_select = &spi_flash_spi_pins[mico_spi_flash.chip_select];
    config.speed       = mico_spi_flash.speed;
    config.mode        = mico_spi_flash.mode;
    config.bits        = mico_spi_flash.bits;

    if ( kNoErr != platform_spi_transfer( &spi_flash_spi, &config, (mico_spi_message_segment_t*)segments, num_segments  ) )
    {
        return -1;
    }

    return 0;
}
#else
int sflash_platform_init( /*@shared@*/ void* peripheral_id, /*@out@*/ void** platform_peripheral_out )
{
    UNUSED_PARAMETER( peripheral_id );
    UNUSED_PARAMETER( platform_peripheral_out );
    return -1;
}

extern int sflash_platform_send_recv( const void* platform_peripheral, /*@in@*//*@out@*/sflash_platform_message_segment_t* segments, unsigned int num_segments )
{
    UNUSED_PARAMETER( platform_peripheral );
    UNUSED_PARAMETER( segments );
    UNUSED_PARAMETER( num_segments );
    return -1;
}
#endif

/* SPDX-License-Identifier: BSD-2-Clause-Patent */
/*
 * Definitions for weak imports that only the macOS 27.3 kernel patches and board objects provide.
 *
 * The static kernel link cannot leave a weak import undefined, as build-sheng-source-storage.py's weak_defaults() notes for
 * BootLog.c. An iPadOS kernel lacks these symbols, so each one here answers the way its user treats an absent symbol. They are
 * weak, so a real definition wins. build-gop-legacy-display-27.py links this file only when the target is not macOS.
 */
#include <stdbool.h>
#include <stdint.h>
#include <mach/kern_return.h>
#include <mach/vm_types.h>

#define WEAK_DEFAULT __attribute__((weak, visibility("hidden")))

/* package/BootLog.c "[cs sha]" row (macOS cssha-digest-time.patch): zero counters. */
WEAK_DEFAULT uint64_t cs_native4k_digest_wall[2];
WEAK_DEFAULT uint64_t cs_native4k_digest_cpu[2];
WEAK_DEFAULT uint64_t cs_native4k_digest_bytes[2];
WEAK_DEFAULT uint64_t cs_native4k_chunk_ticks;
WEAK_DEFAULT uint64_t cs_native4k_record_ticks;

/* drivers/RamBlock NativeRamBlock.cpp (macOS payload-addon-release.patch): the loader memory stays reserved. */
WEAK_DEFAULT bool ml_static_mfree_prepare(vm_offset_t address, vm_size_t size)
{
    (void)address;
    (void)size;
    return false;
}

/* drivers/Adreno740 NativeAdrenoPublish.cpp (macOS gpupool-device-pager-close.patch): no close report, so the view stays
 * untracked, as without the hook. */
WEAK_DEFAULT kern_return_t iokit_physical_descriptor_close_notify(void *descriptor, void (*closed)(void *), void *context)
{
    (void)descriptor;
    (void)closed;
    (void)context;
    return KERN_NOT_SUPPORTED;
}

/* package/LegacyDisplayProbe.cpp: the iPadOS 17 request layout, which is its own fallback when the display has none. */
WEAK_DEFAULT const unsigned native_legacy_request_layout[6] = {17, 81, 792, 804, 816, 2624};

/* package/LegacyDisplayProbe.cpp: the macOS Ethernet and software AES probes (ShengEthernet.cpp, SoftwareAesProbe.cpp). */
WEAK_DEFAULT void sheng_ethernet_probe(void)
{
}

WEAK_DEFAULT void sheng_software_aes_probe(void)
{
}

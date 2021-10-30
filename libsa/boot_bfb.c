/**
 *  @file boot_bfb.c
 *  @author MOBIUSLOOPFOUR <scratch.joint-0i@icloud.com>
 *
 *  Copyright MOBIUSLOOPFOUR 2021
 *  All rights reserved.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @brief Basic impl. of the POSIX libc string functions. strdup will not be implemented
 *          in kernel space. (malloc)
 *
 */



#include "bateau.h"
#include <uefi.h>

#include "bootf.h" /* boot failures */

bframebuffer_t *
make_bframebuffer(void)
{
    bframebuffer_t      *sbuf               = malloc(sizeof(bframebuffer_t));
    efi_status_t        status;
    efi_guid_t          gop_guid            = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t           *gop                = NULL;
    efi_gop_mode_info_t *info               = NULL;
    uintn_t             isiz                = sizeof(efi_gop_mode_info_t);

    

    status = BS->LocateProtocol(&gop_guid, NULL, (void**)&gop);
    if ((EFI_ERROR(status)) && !gop) {
		printf("Could not make a gop: (error code %d)\n", __LINE__);
        boot_failure_feedback();
		return sbuf;
	}
    

    /* get current mode */
    status = gop->QueryMode(gop, gop->Mode ? gop->Mode->Mode : 0, &isiz, &info);

    

    if (EFI_ERROR(status)) {
        printf("Could not make a gop: (error code %d)\n", __LINE__);
        boot_failure_feedback();
		return sbuf;
    }

    

    /* make the struct */
    sbuf->base                              = (void*)gop->Mode->FrameBufferBase;
    sbuf->size                              = gop->Mode->FrameBufferSize;
    sbuf->x                                 = info->HorizontalResolution;
    sbuf->y                                 = info->VerticalResolution;
    sbuf->pixels_per_scanl                  = info->PixelsPerScanLine;

    

    return sbuf;
}

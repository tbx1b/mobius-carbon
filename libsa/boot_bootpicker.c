/**
 *  @file boot_bootpicker.c
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
 *  @brief Kernel bootloader
 *
 */

#include <uefi.h>
#include "bateau.h"
/* ELF loader */
extern int stald(char *path, void *argv);
/* bfb.c */
extern bframebuffer_t *make_bframebuffer(void);
/* memmap.c */
extern bateau_memmap_result_t make_memmap(void);



/* framebuffer properties */
unsigned int width, height, pitch;
unsigned char *lfb;
/* font to be used */
ssfn_font_t *font;


#include "bootf.h"

int main(void)
{
    bateau_info_struct_t *b_info = malloc(sizeof(bateau_info_struct_t));
    b_info->frame_buffer = make_bframebuffer();

    bateau_memmap_result_t memmap_result = make_memmap();
    b_info->memmap = memmap_result.memmap;
    b_info->memmap_descriptor_size = memmap_result.memmap_descriptor_size;
    b_info->memmap_size = memmap_result.memmap_size;

    /* prevent UB */
    for (size_t i = 0; i < 0x100; i++) {
        b_info->options[i] = 0;
    }

    efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t *gop = NULL;
    FILE *f;
    long int size;

    if((f = fopen("\\System\\Stash\\Resources\\Console.cff", "r"))) {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        font = (ssfn_font_t*)malloc(size + 1);
        if(!font) {
            printf("unable to allocate memory\n");
            return 1;
        }
        fread(font, size, 1, f);
        fclose(f);
    } else {
        printf("Unable to load font\n");
        while (1) {}
    }

    BS->LocateProtocol(&gopGuid, NULL, (void**)&gop);
    //if(!EFI_ERROR(status) && gop) {
        //status = gop->SetMode(gop, 0);
        //ST->ConOut->Reset(ST->ConOut, 0);
        //ST->StdErr->Reset(ST->StdErr, 0);
        //if(EFI_ERROR(status)) {
        //    printf("unable to set video mode\n");
        //    return 0;
        //}
        /* set up destination buffer */
    lfb = (unsigned char*)gop->Mode->FrameBufferBase;
    width = gop->Mode->Information->HorizontalResolution;
    height = gop->Mode->Information->VerticalResolution;
    pitch = sizeof(unsigned int) * gop->Mode->Information->PixelsPerScanLine;
    //} else {
    //    printf("unable to get graphics output protocol\n");
    //    return 0;
    //}

    b_info->font = font;
    b_info->height = height;
    b_info->width = width;
    b_info->lfb = lfb;
    b_info->pitch = pitch;
    
    printf("Memmap entries: %d\n", b_info->memmap_size / b_info->memmap_descriptor_size);
    stald("\\System\\Kernel\\a.out", b_info);
}

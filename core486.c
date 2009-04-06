#include "minx86dec/state.h"
#include "minx86dec/opcodes.h"

static minx86_read_ptr_t cip;
#include "minx86dec/x86_core_macros.h"

void minx86dec_decode486(struct minx86dec_state *state,struct minx86dec_instruction *ins) {
	register unsigned int patience = 6;
	cip = state->read_ip;
#define core_level 4
#define isdata32 ins->data32
#define isaddr32 ins->addr32

	/* default to 8086-style invalid opcode (apparently there was no invalid opcode exception?) */
	ins->data32 = state->data32;
	ins->addr32 = state->addr32;
	ins->start = state->read_ip;
	ins->opcode = MXOP_UD;
	ins->segment = -1;
	ins->argc = 0;

	/* bring in the core.
	 * don't bitch about ugliness, this avoid maintaining multiple copies of the same code.
	 * and DOSBox does this too to keep it's various "cores" clean, so there. */
	{
#include "x86_core.h"
	}

	/* invalid opcode. step 1 forward */
	if (ins->opcode == MXOP_UD)
		ins->end = state->read_ip = (ins->start + 1);
	else
		ins->end = state->read_ip = cip;
}

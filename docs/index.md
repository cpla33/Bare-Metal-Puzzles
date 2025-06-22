# Flash RP2040

Here's how to flash the RP2040:

```bash
openocd -f interface/picoprobe.cfg -f target/rp2040.cfg \
  -c "adapter speed 5000" \
  -c "init" -c "reset halt" \
  -c "program part2.bin verify reset exit"


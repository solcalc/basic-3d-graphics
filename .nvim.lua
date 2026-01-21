vim.api.nvim_set_keymap("n", "<Leader>B", ":wa<CR>:!clang main.c -o main -lraylib -lm<CR>", { desc = "Run build task" })
vim.api.nvim_set_keymap("n", "<Leader>R", ":!./main<CR>", { desc = "Run program" })

-- In your init.lua or in a keymaps file
vim.keymap.set('n', ']]', ']m', { noremap = true, silent = true })
vim.keymap.set('n', '[[', '[m', { noremap = true, silent = true })


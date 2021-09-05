library(ggplot2)
library(reshape2)

df <- read.csv("perfdata.csv") %>%
  mutate(Version = as.integer(gsub("\\..*", "", as.character(Version)))) %>%
  group_by(CPU, Compiler, Version, Iterations) %>%
  mutate(Speedup = max(ifelse(Program == "boost", NA, Runtime), na.rm = T) / Runtime) %>%
  ungroup()

filter(df, CPU == "Xeon E2695v3", Compiler == "g++", Version == "10") %>%
  ggplot(aes(x = reorder(Program, -Runtime), y = Runtime)) +
  geom_bar(stat = "identity") +
  geom_text(aes(label = paste0(round(Speedup, 2), "x")), color = "red") +
  ylab("Minimum run time (s)") +
    xlab("Implementation") +
    coord_flip()

ggsave("base-2695-g++10.png")

filter(df, CPU == "Xeon E2695v3", Compiler == "clang++", Version == "12") %>%
  ggplot(aes(x = reorder(Program, -Runtime), y = Runtime)) +
  geom_bar(stat = "identity") +
  geom_text(aes(label = paste0(round(Speedup, 2), "x")), color = "red") +
  ylab("Minimum run time (s)") +
  xlab("Implementation") +
  coord_flip()

ggsave("base-2695-clang++12.png")


filter(df, CPU == "Xeon E2695v3") %>%
  ggplot(aes(x = Version, y = Runtime, color = Compiler)) +
  geom_line() +
  geom_point() +
  facet_wrap(~ Program, scales = "free") +
  scale_x_discrete(name = "Compiler version", limits = seq(5, 12), labels = seq(5, 12)) +
  ylab("Minimum run time (s)")

ggsave("compiler-comparison.png", units = "cm", width = 30, height = 20, dpi = 600)

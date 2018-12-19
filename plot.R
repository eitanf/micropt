library(ggplot2)
library(reshape2)

df <- read.table ("perf.dat")
df$Implementation<-factor(df$Implementation, levels=df$Implementation)
dfm <- melt(df[,c(1,3,4,5)],id.vars=1)
colnames(dfm)[2] = "Platform"
ggplot(dfm,aes(x=Implementation, y=value)) +
  geom_bar(aes(fill=Platform), stat="identity", position="dodge") +
  ylab("Run time (s)") +
  theme(axis.text.x = element_text(angle=45, hjust=1))

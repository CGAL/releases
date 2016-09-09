#line 221 "funnelweb.fw"
(defun fw-mode ()
  (c++-mode)
  (setq indent-tabs-mode nil))


(setq auto-mode-alist
      (append  '(("\\.fw$"  . fw-mode))
               auto-mode-alist)
)

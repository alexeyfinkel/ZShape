In order to get the EffxAcc code to compile, one must first use the latest and greatest version of the Tag&Probe tools.

cvs co -r V01-05-00 PhysicsTools/TagAndProbe

----------------------------

FOR PDFS:

     1) Edit the file 
    $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/lhapdf.xml
      2.a) In that file, change the default for LHAPDF_BASE to 
            "/local/cms/other/lhapdf/lhapdf-5.8.6"
      2.b) Change also the field "version" in order to match 
            your installed version
      3) scram setup lhapdf (and check that environment 
            variables point to /local/cms/other/...)
      4) cmsenv
      5) scram b

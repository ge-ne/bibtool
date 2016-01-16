%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 
%% This file is part of BibTool.
%% It is distributed under the GNU General Public License.
%% See the file COPYING for details.
%% 
%% (c) 2012-2016 Gerd Neugebauer
%% 
%% Net: gene@gerd-neugebauer.de
%%
%% This program is free software; you can redistribute it and/or modify
%% it under the terms of the GNU General Public License as published by
%% the Free Software Foundation; either version 2, or (at your option)
%% any later version.
%%
%% This program is distributed in the hope that it will be useful,
%% but WITHOUT ANY WARRANTY; without even the implied warranty of
%% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%% GNU General Public License for more details.
%%
%% You should have received a copy of the GNU General Public License
%% along with this program; if not, write to the Free Software
%% Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Entry types for bibLaTeX
%
new.entry.type{Article}
new.entry.type{Book}
new.entry.type{MVBook}
new.entry.type{InBook}
new.entry.type{BookInBook}
new.entry.type{SuppBook}
new.entry.type{Booklet}
new.entry.type{Collection}
new.entry.type{MVCollection}
new.entry.type{InCollection}
new.entry.type{SuppCollection}
new.entry.type{Manual}
new.entry.type{Misc}
new.entry.type{Online}
new.entry.type{Patent}
new.entry.type{Periodical}
new.entry.type{SuppPeriodical}
new.entry.type{Proceedings}
new.entry.type{MVProceedings}
new.entry.type{Reference}
new.entry.type{MVReference}
new.entry.type{Inreference}
new.entry.type{Report}
new.entry.type{Set}
new.entry.type{Thesis}
new.entry.type{Unpublished}
new.entry.type{Cdata}
new.entry.type{CustomA}
new.entry.type{CustomB}
new.entry.type{CustomC}
new.entry.type{CustomD}
new.entry.type{CustomE}
new.entry.type{CustomF}
new.entry.type{Conference}
new.entry.type{Electronic}
new.entry.type{MasterThesis}
new.entry.type{PhdThesis}
new.entry.type{TechReport}
new.entry.type{WWW}

new.entry.type{Artwork}
new.entry.type{Audio}
new.entry.type{BibNote}
new.entry.type{Commentary}
new.entry.type{Image}
new.entry.type{Jurisdiction}
new.entry.type{Legislation}
new.entry.type{Legal}
new.entry.type{Letter}
new.entry.type{Movie}
new.entry.type{Music}
new.entry.type{Performance}
new.entry.type{Review}
new.entry.type{Software}
new.entry.type{Standard}
new.entry.type{Video}
%
% Field capitalization for bibLaTeX
%
% special fields
new.field.type { entryset        = EntrySet        }
new.field.type { entrysubtype    = EntrySubtype    }
new.field.type { execute         = Execute         }
new.field.type { hyphenation     = Hyphenation     }
new.field.type { keywords        = Keywords        }
new.field.type { label           = Label           }
new.field.type { options         = Options         }
new.field.type { presort         = Presort         }
new.field.type { shorthand       = Shorthand       }
new.field.type { sortkey         = SortKey         }
new.field.type { sortname        = SortName        }
new.field.type { sorttitle       = SortTitle       }
new.field.type { sortyear        = SortYear        }
new.field.type { crossref        = CrossRef        }
new.field.type { xdata           = XData           }
new.field.type { xref            = XRef            }
% data fields
new.field.type { abstract        = Abstract        }
new.field.type { addendum        = Addendum        }
new.field.type { address         = Address         }
new.field.type { afterword       = Afterword       }
new.field.type { annotation      = Annotation      }
new.field.type { annote          = Annote          }
new.field.type { annotator       = Annotator       }
new.field.type { author          = Author          }
new.field.type { authortype      = AuthorType      }
new.field.type { bookauthor      = BookAuthor      }
new.field.type { booksubtitle    = BookSubtitle    }
new.field.type { booktitle       = BookTitle       }
new.field.type { booktitleaddon  = BookTitleAddOn  }
new.field.type { chapter         = Chapter         }
new.field.type { commentator     = Commentator     }
new.field.type { date            = Date            }
new.field.type { doi             = DOI             }
new.field.type { edition         = Edition         }
new.field.type { editor          = Editor          }
new.field.type { editora         = EditorA         }
new.field.type { editorb         = EditorB         }
new.field.type { editorc         = EditorC         }
new.field.type { editortype      = EditorType      }
new.field.type { editoratype     = EditorAType     }
new.field.type { editorbtype     = EditorBType     }
new.field.type { editorctype     = EditorCType     }
new.field.type { eid             = EID             }
new.field.type { eprint          = EPrint          }
new.field.type { eprintclass     = EPrintClass     }
new.field.type { eprinttype      = EPrintType      }
new.field.type { eventdate       = EventDate       }
new.field.type { eventtitle      = EventTitle      }
new.field.type { file            = File            }
new.field.type { foreword        = Foreword        }
new.field.type { gender          = Gender          }
new.field.type { howpublished    = HowPublished    }
new.field.type { indexsorttitle  = IndexSortTitle  }
new.field.type { indextitle      = IndexTitle      }
new.field.type { institution     = Institution     }
new.field.type { introduction    = Introduction    }
new.field.type { isan            = ISAN            }
new.field.type { isbn            = ISBN            }
new.field.type { ismn            = ISMN            }
new.field.type { isrn            = ISRN            }
new.field.type { issn            = ISSN            }
new.field.type { issue           = Issue           }
new.field.type { issuetitle      = IssueTitle      }
new.field.type { issuesubtitle   = IssueSubtitle   }
new.field.type { iswc            = ISWC            }
new.field.type { journal         = Journal         }
new.field.type { journaltitle    = JournalTitle    }
new.field.type { journalsubtitle = JournalSubtitle }
new.field.type { language        = Language        }
new.field.type { library         = Library         }
new.field.type { location        = Location        }
new.field.type { bookpagination  = BookPagination  }
new.field.type { mainsubtitle    = MainSubtitle    }
new.field.type { maintitle       = MainTitle       }
new.field.type { maintitleaddon  = MainTitleAddOn  }
new.field.type { month           = Month           }
new.field.type { nameaddon       = NameAddOn       }
new.field.type { note            = Note            }
new.field.type { number          = Number          }
new.field.type { organization    = Organization    }
new.field.type { origlanguage    = OrigLanguage    }
new.field.type { origlocation    = OrigLocation    }
new.field.type { origpublisher   = OrigPublisher   }
new.field.type { origtitle       = OrigTitle       }
new.field.type { origdate        = OrigDate        }
new.field.type { pages           = Pages           }
new.field.type { pagetotal       = PageTotal       }
new.field.type { pagination      = Pagination      }
new.field.type { part            = Part            }
new.field.type { pdf             = PDF             }
new.field.type { pubstate        = PubState        }
new.field.type { reprinttitle    = ReprintTitle    }
new.field.type { holder          = Holder          }
new.field.type { publisher       = Publisher       }
new.field.type { school          = School          }
new.field.type { series          = Series          }
new.field.type { shortauthor     = ShortAuthor     }
new.field.type { shorteditor     = ShortEditor     }
new.field.type { shorthandintro  = ShorthandIntro  }
new.field.type { shortjournal    = ShortJournal    }
new.field.type { shortseries     = ShortSeries     }
new.field.type { shorttitle      = ShortTitle      }
new.field.type { subtitle        = Subtitle        }
new.field.type { title           = Title           }
new.field.type { titleaddon      = TitleAddOn      }
new.field.type { translator      = Translator      }
new.field.type { type            = Type            }
new.field.type { url             = URL             }
new.field.type { urldate         = URLDate         }
new.field.type { venue           = Venue           }
new.field.type { version         = Version         }
new.field.type { volume          = Volume          }
new.field.type { volumes         = Volumes         }
new.field.type { year            = Year            }
% aliases
new.field.type { archiveprefix	 =  ArchivePrefix  }
new.field.type { primaryclass	 =  PrimaryClass   }
% custom fields
new.field.type { namea		 =  NameA	   }
new.field.type { nameb		 =  NameB	   }
new.field.type { namec		 =  NameC	   }
new.field.type { nameatype	 =  NameAType	   }
new.field.type { namebtype	 =  NameBType	   }
new.field.type { namectype	 =  NameCType	   }
new.field.type { lista		 =  ListA	   }
new.field.type { listb		 =  ListB	   }
new.field.type { listc		 =  ListC	   }
new.field.type { listd		 =  ListD	   }
new.field.type { liste		 =  ListE	   }
new.field.type { listf		 =  ListF	   }
new.field.type { usera		 =  UserA	   }
new.field.type { userb		 =  UserB	   }
new.field.type { userc		 =  UserC	   }
new.field.type { userd		 =  UserD	   }
new.field.type { usere		 =  UserE	   }
new.field.type { userf		 =  UserF	   }
new.field.type { verba		 =  VerbA	   }
new.field.type { verbb		 =  VerbB	   }
new.field.type { verbc		 =  VerbC	   }

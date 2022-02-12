import { Injectable } from "@angular/core";
import { Title } from "@angular/platform-browser"

@Injectable({providedIn: "root"})
export class PageTitleService {
  constructor(private title: Title) {}

  updatePageTitle() {
    this.title.setTitle("Reminder")
  }
}

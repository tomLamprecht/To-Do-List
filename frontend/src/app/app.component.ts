import { Component, OnInit } from '@angular/core';
import { PageTitleService } from 'src/lib/feature/page-title.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'],
})
export class AppComponent implements OnInit {


  constructor(private pageTitleService: PageTitleService) {}

  ngOnInit(): void {
      this.pageTitleService.updatePageTitle();
  }

}

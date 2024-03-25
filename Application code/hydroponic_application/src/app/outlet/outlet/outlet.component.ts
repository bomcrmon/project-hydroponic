import { Component, OnInit } from '@angular/core';
import { AuthService } from 'src/app/service/auth.service';


@Component({
  selector: 'app-outlet',
  templateUrl: './outlet.component.html',
  styleUrls: ['./outlet.component.css'],
})
export class OutletComponent implements OnInit {
  isBar:any
  menu_id:any
  menu_list:any
  breadcrumb:any
  userData:any
  permission:any
  show:any
  constructor(private auth: AuthService) {}
  ngOnInit(): void {}

  logout(){
    this.auth.logout();
    }
}
